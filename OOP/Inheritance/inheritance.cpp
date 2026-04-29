#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <set>
#include <variant>
#include <vector>

namespace InheritanceOfImplementation
{
    class Set : std::set<int>
    {
        using BaseImpl = std::set<int>;

    public:
        using BaseImpl::BaseImpl;

        size_t size() const
        {
            return BaseImpl::size();
        }

        const int& operator[](size_t index) const
        {
            return *std::next(BaseImpl::begin(), index);
        }

        bool add_item(int value)
        {
            return BaseImpl::insert(value).second;
        }

        bool remove_item(int value)
        {
            return BaseImpl::erase(value) > 0;
        }
    };

} // namespace InheritanceOfImplementation

namespace InheritanceOfInterface
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
        virtual std::string format(const std::string& data) override
        {
            std::string transformed_data{data};

            std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::tolower(c); });

            return transformed_data;
        }
    };

    class CapitalizeFormatter : public Formatter
    {
    public:
        virtual std::string format(const std::string& data) override
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
} // namespace InheritanceOfInterface

void inheritance_of_interface()
{
    using namespace InheritanceOfInterface;

    Logger logger{std::make_unique<UpperCaseFormatter>()};
    logger.log("Hello, World!");

    logger = Logger{std::make_unique<LowerCaseFormatter>()};
    logger.log("Hello, World!");

    logger = Logger{std::make_unique<CapitalizeFormatter>()};
    logger.log("Hello, World!");
}

void inheritance_of_implementation()
{
    using namespace InheritanceOfImplementation;

    Set values = {3, 2, 1, 5, 6};
    values.add_item(4);
    values.add_item(4);
    values.add_item(3);
    values.add_item(0);

    values.remove_item(2);
    values.remove_item(5);

    for (size_t i = 0u; i < values.size(); ++i)
    {
        std::cout << values[i] << ' ';
    }
}

int main()
{
    inheritance_of_interface();

    std::cout << "\n\n";

    inheritance_of_implementation();
}