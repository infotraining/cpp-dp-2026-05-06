#include "starbugs_coffee.hpp"

#include <memory>

void client(std::unique_ptr<Coffee> coffee)
{
    std::cout << "Description: " << coffee->get_description() << "; Price: " << coffee->get_total_price() << std::endl;
    coffee->prepare();
}

// CoffeeBuilder: Fluent builder for Coffee decorators
class CoffeeBuilder
{
    std::unique_ptr<Coffee> coffee_;

public:
    CoffeeBuilder() = default;

    template <typename Base, typename... Args>
    CoffeeBuilder& create_base(Args&&... args)
    {
        static_assert(std::is_base_of<Coffee, Base>::value, "Base must derive from Coffee");
        coffee_ = std::make_unique<Base>(std::forward<Args>(args)...);
        return *this;
    }

    template <typename... Decorator>
    CoffeeBuilder& add()
    {
        static_assert((std::is_base_of<Coffee, Decorator>::value && ...), "All Decorators must derive from Coffee");
        (..., (coffee_ = std::make_unique<Decorator>(std::move(coffee_))));
        return *this;
    }

    std::unique_ptr<Coffee> get_coffee()
    {
        return std::move(coffee_);
    }
};


int main()
{
    std::unique_ptr<Coffee> cf = std::make_unique<Espresso>();
    client(std::move(cf));

    // TODO: create a coffee decorated with ExtraEspresso, Whisky & WhippedCream. Pass decorated coffee to the client.
    std::unique_ptr<Coffee> fancy_coffee = std::make_unique<Espresso>();
    fancy_coffee = std::make_unique<ExtraEspresso>(std::move(fancy_coffee));
    fancy_coffee = std::make_unique<Whisky>(std::move(fancy_coffee));
    fancy_coffee = std::make_unique<WhippedCream>(std::move(fancy_coffee));
    client(std::move(fancy_coffee));

    // auto coffee = std::make_unique<ExtraEspresso>(std::make_unique<Whisky>(std::make_unique<WhippedCream>(std::make_unique<Espresso>())));

    CoffeeBuilder coffee_bld;
    coffee_bld
        .create_base<Espresso>()
            .add<Whisky>()
            .add<ExtraEspresso, Whisky, WhippedCream>();

    client(std::move(coffee_bld.get_coffee()));
}


