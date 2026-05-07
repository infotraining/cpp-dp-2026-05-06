#include <cassert>
#include <iostream>
#include <memory>
#include <typeinfo>

class Engine
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual std::unique_ptr<Engine> clone() const = 0;
    virtual ~Engine() = default;
};

// CRTP - Curiously Recurring Template Parameter
template <typename TEngine, typename TEngineBase = Engine>
class CloneableEngine : public TEngineBase
{
public:
    std::unique_ptr<Engine> clone() const override
    {
        return std::make_unique<TEngine>(static_cast<const TEngine &>(*this));
    }
};

class Diesel : public CloneableEngine<Diesel>
{
public:
    void start() override
    {
        std::cout << "Diesel starts\n";
    }

    void stop() override
    {
        std::cout << "Diesel stops\n";
    }

    // std::unique_ptr<Engine> clone() const override
    // {
    //     return std::make_unique<Diesel>(*this);
    // }
};

class TDI : public CloneableEngine<TDI, Diesel>
{
public:
    void start() override
    {
        std::cout << "TDI starts\n";
    }

    void stop() override
    {
        std::cout << "TDI stops\n";
    }

    // std::unique_ptr<Engine> clone() const override
    // {
    //     return std::make_unique<TDI>(*this);
    // }
};

class Hybrid : public CloneableEngine<Hybrid>
{
public:
    void start() override
    {
        std::cout << "Hybrid starts\n";
    }

    void stop() override
    {
        std::cout << "Hybrid stops\n";
    }

    // std::unique_ptr<Engine> clone() const override
    // {
    //     return std::make_unique<Hybrid>(*this);
    // }
};

class Hydrogen : public CloneableEngine<Hydrogen>
{
public:
    void start() override
    {
        std::cout << "Hydrogen starts\n";
    }

    void stop() override
    {
        std::cout << "Hydrogen stops\n";
    }
};

class Car
{
    std::unique_ptr<Engine> engine_;

public:
    explicit Car(std::unique_ptr<Engine> engine)
        : engine_{std::move(engine)}
    {
    }

    Car(const Car &source) : engine_{source.engine_->clone()}
    {
    }

    void drive(int km)
    {
        engine_->start();
        std::cout << "Driving " << km << " kms\n";
        engine_->stop();
    }
};

namespace Cpp26
{
    class Engine
    {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual ~Engine() = default;
    };

    class Diesel : public Engine
    {
    public:
        Diesel() = default;

        Diesel(const Diesel &source)
        {
            std::cout << "Diesel(cc)\n";
        }

        Diesel(Diesel&&) = default;

        void start() override
        {
            std::cout << "Diesel starts\n";
        }

        void stop() override
        {
            std::cout << "Diesel stops\n";
        }
    };

    class TDI : public Diesel
    {
    public:
        TDI() = default;

        TDI(const TDI &source)
        {
            std::cout << "TDI(cc)\n";
        }

        TDI(TDI&&) = default;

        void start() override
        {
            std::cout << "TDI starts\n";
        }

        void stop() override
        {
            std::cout << "TDI stops\n";
        }
    };

    class Hybrid : public Engine
    {
    public:
        Hybrid() = default;

        Hybrid(const Hybrid &source)
        {
            std::cout << "Hybrid(cc)\n";
        }

        Hybrid(Hybrid&&) = default;

        void start() override
        {
            std::cout << "Hybrid starts\n";
        }

        void stop() override
        {
            std::cout << "Hybrid stops\n";
        }
    };

    class Hydrogen : public Engine
    {
    public:
        Hydrogen() = default;

        Hydrogen(const Hydrogen &source)
        {
            std::cout << "Hydrogen(cc)\n";
        }

        Hydrogen(Hydrogen&&) = default;

        void start() override
        {
            std::cout << "Hydrogen starts\n";
        }

        void stop() override
        {
            std::cout << "Hydrogen stops\n";
        }
    };

    class Car
    {
        std::polymorphic<Engine> engine_;

    public:
        template <typename TEngine>
        explicit Car(TEngine engine)
            : engine_{std::move(engine)}
        {
        }

        void drive(int km)
        {
            engine_->start();
            std::cout << "Driving " << km << " kms\n";
            engine_->stop();
        }
    };
}

void polymorhic_pointer()
{
    std::polymorphic<Cpp26::Engine> e1{Cpp26::Diesel{}};

    e1->start();
    e1->stop();

    std::polymorphic<Cpp26::Engine> e2 = e1;
    e2->start();
    e2->stop();
}

int main()
{
    // polymorhic_pointer();
    
    Cpp26::Car c1{Cpp26::Hydrogen{}};
    c1.drive(100);

    std::cout << "\n";

    Cpp26::Car c2 = c1;
    c2.drive(200);

    std::cout << "\n";
}
