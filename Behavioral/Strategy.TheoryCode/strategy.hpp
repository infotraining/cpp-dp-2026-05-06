#ifndef STRATEGY_HPP_
#define STRATEGY_HPP_

#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <cctype>
#include <string>

// "Strategy"
class Formatter
{
public:
    virtual std::string format(const std::string& data) = 0;
    virtual ~Formatter() = default;
};

// "ConcreteStrategyA"
class UpperCaseFormatter : public Formatter
{
public:
    std::string format(const std::string& data) override
    {
        std::string transformed_data{data};

        std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::toupper(c); });

        return transformed_data;
    }
};

// "ConcreteStrategyB"
class LowerCaseFormatter : public Formatter
{
public:
    std::string format(const std::string& data) override
    {
        std::string transformed_data{data};

        std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::tolower(c); });

        return transformed_data;
    }
};

// "ConcreteStrategyC"
class CapitalizeFormatter : public Formatter
{
public:
    std::string format(const std::string& data) override
    {
        std::string transformed_data{data};

        if (data.size() >= 1)
        {
            transformed_data[0] = static_cast<char>(std::toupper(data.front()));

            std::transform(data.begin() + 1, data.end(), transformed_data.begin() + 1, [](char c) { return std::tolower(c); });
        }

        return transformed_data;
    }
};

// "Context"
class DataContext
{
    std::shared_ptr<Formatter> strategy_;
    std::string data_ = "text";

public:
    DataContext(std::shared_ptr<Formatter> strategy) : strategy_{strategy}
    {
    }

    void reset_formatter(std::shared_ptr<Formatter> new_strategy)
    {
        strategy_ = new_strategy;
    }

    void pretty_print()
    {
        std::cout << "Data: " << strategy_->format(data_) << std::endl;
    }

    std::string data() const
    {
        return data_;
    }

    void set_data(const std::string& data)
    {
        data_ = data;
    }
};

#endif /*STRATEGY_HPP_*/
