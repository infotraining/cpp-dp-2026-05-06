#ifndef MONSTERS_HPP_
#define MONSTERS_HPP_

#include <iostream>
#include <string>

namespace Game
{
    class Enemy
    {
    public:
        virtual void action() = 0;
        virtual ~Enemy() = default;
    };

    class Soldier : public Enemy
    {
    };

    class Monster : public Enemy
    {
    };

    class SuperMonster : public Enemy
    {
    };

    //////////////////////////////////////////////////
    // Concrete Enemies
    //////////////////////////////////////////////////

    class SillySoldier : public Soldier
    {
    public:
        void action()
        {
            std::cout << "SillySoldier Action" << std::endl;
        }
    };

    class SillyMonster : public Monster
    {
    public:
        void action() override
        {
            std::cout << "SillyMonster Action" << std::endl;
        }
    };

    class SillySuperMonster : public SuperMonster
    {
    public:
        void action() override
        {
            std::cout << "SillySuperMonster Action" << std::endl;
        }
    };

    class BadSoldier : public Soldier
    {
    public:
        void action() override
        {
            std::cout << "BadSoldier Action" << std::endl;
        }
    };

    class BadMonster : public Monster
    {
    public:
        void action() override
        {
            std::cout << "BadMonster Action" << std::endl;
        }
    };

    class BadSuperMonster : public SuperMonster
    {
    public:
        void action() override
        {
            std::cout << "BadSuperMonster Action" << std::endl;
        }
    };
};

#endif /*MONSTERS_HPP_*/
