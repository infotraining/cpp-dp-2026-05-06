#include "chain.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <cstdint>

using namespace std;

struct Fan
{
    std::string name_;
    uint8_t speed_{};

public:
    Fan(std::string name)
        : name_{std::move(name)}
    { }

    void on()
    {
        speed_ = 1;
        cout << "Fan(" << name_ << ") is on\n";
    }

    void off()
    {
        speed_ = 0;
        cout << "Fan(" << name_ << ") is off\n";
    }

    bool is_on() const
    {
        return speed_ > 0;
    }

    void set_speed(uint8_t speed)
    {
        speed_ = std::clamp(speed, uint8_t{0}, uint8_t{10});
        cout << "Fan(" << name_ << ") speed is set to " << static_cast<int>(speed) << '\n';
    }

    uint8_t speed() const
    {
        return speed_;
    }
};

struct Heater
{
    bool is_on_{};

public:
    void on()
    {
        cout << "Heater is on\n";
        is_on_ = true;
    }

    void off()
    {
        cout << "Heater is off\n";
        is_on_ = false;
    }

    bool is_on() const
    {
        return is_on_;
    }
};

namespace Matchers
{
    template <typename Compare>
    struct Comparer
    {
        auto operator()(Temperature temperature) const
        {
            return [temperature, compare = Compare{}](Temperature value) {
                return compare(value, temperature);
            };
        }
    };

    auto _ = [](Temperature temperature) {
        return true;
    };
    // auto Lt = [](Temperature value) { return [value](Temperature temperature) { return temperature < value; }; };
    auto Lt = Comparer<std::less<>>{};
    auto Le = Comparer<std::less_equal<>>{};
    auto Gt = Comparer<std::greater<>>{};
    auto Ge = Comparer<std::greater_equal<>>{};
    auto Eq = Comparer<std::equal_to<>>{};

    auto And = [](auto&& lhs, auto&& rhs) {
        return [lhs = std::forward<decltype(lhs)>(lhs), rhs = std::forward<decltype(rhs)>(rhs)](Temperature temperature) {
            return lhs(temperature) && rhs(temperature);
        };
    };

    auto Or = [](auto&& lhs, auto&& rhs) {
        return [lhs = std::forward<decltype(lhs)>(lhs), rhs = std::forward<decltype(rhs)>(rhs)](Temperature temperature) {
            return lhs(temperature) || rhs(temperature);
        };
    };

    auto Not = [](auto&& pred) {
        return [pred = std::forward<decltype(pred)>(pred)](Temperature temperature) {
            return !pred(temperature);
        };
    };
} // namespace Matchers

int main()
{
    std::cout << "Start...\n";

    Fan fan_1{"Small"};
    Fan fan_2{"Big"};
    Heater heater;

    Device device{"Temperature Control"};

    // commands
    auto turn_on_heater = [&heater]() {
        if (!heater.is_on())
            heater.on();
    };

    auto turn_off_heater = [&heater]() {
        if (heater.is_on())
            heater.off();
    };

    auto turn_on_fan_1 = [&fan_1]() {
        if (!fan_1.is_on())
            fan_1.on();
    };

    auto turn_off_fan_1 = [&fan_1]() {
        if (fan_1.is_on())
            fan_1.off();
    };

    auto turn_on_fan_2 = [&fan_2]() {
        if (!fan_2.is_on())
            fan_2.on();
    };

    auto turn_off_fan_2 = [&fan_2]() {
        if (fan_2.is_on())
            fan_2.off();
    };

    auto set_fan_speed = [](Fan& fan, uint8_t speed) {
        return [&fan, speed]() {
            if (fan.speed() != speed)
                fan.set_speed(speed);
        };
    };

    using namespace Matchers;

    device.add_handler(/*[](Temperature temperature) {
                            return temperature < 19.0;
                       },*/
        Lt(19.0),
        [&](Temperature temperature) {
            turn_on_heater();
            turn_off_fan_1();
            turn_off_fan_2();
        });

    device.add_handler(/*[](Temperature temperature) { return temperature >= 20.0; },*/
        Ge(20.0),
        [&](Temperature temperature) {
            turn_off_heater();
        });

    device.add_handler(/*[](Temperature temperature) { return temperature >= 22.5 && temperature < 25; },*/
        And(Ge(22.5), Lt(25.0)),
        [&](Temperature temperature) {
            set_fan_speed(fan_1, 5)();
            turn_off_fan_2();
        });

    device.add_handler(/*[](Temperature temperature) { return temperature >= 25.0; },*/
        Ge(25.0),
        [&](Temperature temperature) {
            set_fan_speed(fan_1, 10)();
            set_fan_speed(fan_2, 10)();
        });

    device.add_handler(_,
        [&](Temperature temperature) {
            std::cout << "Temperature is " << temperature << " degrees..." << std::endl;
        });

    // set of temperatures from 18 to 26 and back to 18 degrees with .5 step with sinusoidal pattern
    std::array temperatures = {18.0, 18.5, 19.0, 19.5, 20.0, 20.5, 21.0, 21.5, 22.0, 22.5, 23.0, 23.5, 24.0, 24.5, 25.0, 25.5, 26.0,
        25.5, 25.0, 24.5, 24.0, 23.5, 23.0, 22.5, 22.0, 21.5, 21.0, 20.5, 20.0, 19.5, 19.0, 18.5, 18.0};

    for (const auto& t : temperatures)
        device.on_temperature_change(t);
}
