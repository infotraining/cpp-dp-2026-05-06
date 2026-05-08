#include "src/turnstile.hpp"
#include <iostream>
#include <variant>
#include <vector>

using namespace std;
using namespace std::literals;

struct PrinterVisitor
{
    void operator()(int i) const
    {
        cout << "int: " << i << endl;
    }

    void operator()(const string& s) const
    {
        cout << "string: " << s << endl;
    }

    void operator()(const vector<int>& v) const
    {
        cout << "vector of ints: ";
        for (const auto& num : v)
        {
            cout << num << " ";
        }
        cout << endl;
    }
};

template <typename... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};

// deduction guide for overloaded - C++17 (since C++20, this is not needed)
template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

void variant_explanation()
{
    std::variant<int, std::string, std::vector<int>> v = 42;

    v = "Hello, World!"s;
    v = std::vector<int>{1, 2, 3, 4, 5};

    if (std::holds_alternative<int>(v))
    {
        std::cout << "Variant holds int: " << std::get<int>(v) << std::endl;
    }
    else if (std::holds_alternative<std::string>(v))
    {
        std::cout << "Variant holds string: " << std::get<std::string>(v) << std::endl;
    }
    else if (std::holds_alternative<std::vector<int>>(v))
    {
        std::cout << "Variant holds vector of ints: ";
        for (const auto& num : std::get<std::vector<int>>(v))
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    PrinterVisitor prn_visitor;
    std::visit(prn_visitor, v);

    auto size_visitor = overloaded{
        [](int i) -> size_t { return i; },
        [](const std::string& s) { return s.size(); },
        [](const std::vector<int>& vec) { return vec.size(); }
    };

    int v_size =std::visit(size_visitor, v);
    std::cout << "Size of the current variant value: " << v_size << std::endl;
}

int main()
{
    variant_explanation();

    TurnstileAPI api;

    Cpp17::Turnstile t{api};

    t.coin();
    t.pass();
    t.pass();
    t.coin();
    t.pass();
    t.coin();
    t.coin();
    t.coin();
}
