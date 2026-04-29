#include "builder.hpp"
#include <iostream>
#include <memory>

using namespace std;

int main()
{
    Director director;

    cout << "Building with EconomyCarBuilder:\n";
    EconomyCarBuilder economy_car_builder;
    director.construct(economy_car_builder);
    Car economy_car = economy_car_builder.get_result();
    std::cout << economy_car.get_configuration();

    cout << "\n\nBuilding with PremiumCarBuilder:\n";
    PremiumCarBuilder premium_car_builder;
    director.construct(premium_car_builder);
    Car premium_car = premium_car_builder.get_result();
    std::cout << premium_car.get_configuration();
}
