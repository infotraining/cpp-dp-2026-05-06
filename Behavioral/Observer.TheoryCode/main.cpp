#include "observer.hpp"

using namespace std;

// Subject
class TemperatureMonitor : public Observable<TemperatureMonitor, double>
{
private:
    double current_temperature_;

public:
    TemperatureMonitor(double temp)
        : current_temperature_{temp}
    {
        std::cout << "Creating an observable " << typeid(*this).name() << this << "\n";
    }

    void set_temperature(double new_temperature)
    {
        if (current_temperature_ != new_temperature)
        {
            current_temperature_ = new_temperature;

            // sending notification to all observers
            notify(*this, current_temperature_);
        }
    }
};

// Observer & Subject
class Fan : public Observer<TemperatureMonitor, double>, public Observable<Fan, const std::string&>
{
    bool is_on_ = false;

public:
    void update(TemperatureMonitor& tm, double current_temperature) override
    {
        if (!is_on_ && current_temperature > 25.0)
            on();

        if (is_on_ && current_temperature < 24.0)
            off();
    }

    void on()
    {
        is_on_ = true;
        notify(*this, "Fan is on...");
    }

    void off()
    {
        is_on_ = false;
        notify(*this, "Fan is off...");
    }
};

// Observer
class ConsoleLogger : public Observer<TemperatureMonitor, double>, public Observer<Fan, const std::string&>
{
public:
    void update(TemperatureMonitor& tm, double current_temperature) override
    {
        std::cout << "ConsoleLogger notified - temperature has changed to " << current_temperature << std::endl;
    }

    void update(Fan& tm, const std::string& message) override
    {
        std::cout << "ConsoleLogger notified - " << message << std::endl;
    }
};

int main()
{
    Fan fan;
    TemperatureMonitor temp_monitor(21.0);
    ConsoleLogger console_logger;

    temp_monitor.subscribe(&fan);
    temp_monitor.subscribe(&console_logger);
    fan.subscribe(&console_logger);

    temp_monitor.set_temperature(22.0);
    temp_monitor.set_temperature(23.0);
    temp_monitor.set_temperature(24.0);
    temp_monitor.set_temperature(25.0);
    temp_monitor.set_temperature(26.0);
    temp_monitor.set_temperature(25.0);
    temp_monitor.set_temperature(24.0);
    temp_monitor.set_temperature(23.0);
    temp_monitor.set_temperature(21.0);

    temp_monitor.unsubscribe(&fan);

    temp_monitor.set_temperature(22.0);
    temp_monitor.set_temperature(23.0);
    temp_monitor.set_temperature(24.0);
    temp_monitor.set_temperature(25.0);
    temp_monitor.set_temperature(26.0);
    temp_monitor.set_temperature(25.0);
    temp_monitor.set_temperature(24.0);
    temp_monitor.set_temperature(23.0);
    temp_monitor.set_temperature(21.0);
}
