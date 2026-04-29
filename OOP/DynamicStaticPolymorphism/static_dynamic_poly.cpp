#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <variant>
#include <vector>
#include <algorithm>

namespace DynamicPolymorphism
{
    class Formatter
    {
    public:
        virtual std::string format(const std::string& data) = 0;
        virtual ~Formatter() = default;
    };

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

    class Logger
    {
        std::unique_ptr<Formatter> formatter_;

    public:
        Logger(std::unique_ptr<Formatter> formatter)
            : formatter_{std::move(formatter)}
        { }

        void log(const std::string& data)
        {
            std::cout << "LOG: " << formatter_->format(data) << '\n';
        }
    };
} // namespace DynamicPolymorphism

namespace StaticPolymorphism
{
    struct UpperCaseFormatter
    {
        std::string format(const std::string& message) const
        {
            std::string result = message;
            std::transform(result.begin(), result.end(),
                result.begin(), [](char c) { return std::toupper(c); });
            return result;
        }
    };

    struct CapitalizeFormatter
    {
        std::string format(const std::string& message) const
        {
            std::string result = message;
            result[0] = std::toupper(result[0]);
            return result;
        }
    };

    template <typename TFormatter = UpperCaseFormatter>
    class Logger
    {
        TFormatter formatter_;

    public:
        Logger() = default;

        Logger(TFormatter formatter)
            : formatter_(std::move(formatter))
        {
        }

        void log(const std::string& message)
        {
            std::cout << formatter_.format(message) << std::endl;
        }
    };
} // namespace StaticPolymorphism

void dynamic_polymorphism()
{
    using namespace DynamicPolymorphism;

    Logger logger{std::make_unique<UpperCaseFormatter>()};
    logger.log("Hello, World!");

    logger = Logger{std::make_unique<LowerCaseFormatter>()};
    logger.log("Hello, World!");

    logger = Logger{std::make_unique<CapitalizeFormatter>()};
    logger.log("Hello, World!");
}

void static_polymorphism()
{
    using namespace StaticPolymorphism;

    Logger logger{UpperCaseFormatter{}};
    logger.log("Hello, World!");

    Logger<CapitalizeFormatter> logger2;
    logger2.log("hello, world!");
}

int main()
{
    dynamic_polymorphism();

    std::cout << "\n\n";

    static_polymorphism();

    std::cout << "\n\n";
}