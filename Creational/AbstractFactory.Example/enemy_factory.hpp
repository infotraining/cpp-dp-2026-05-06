#ifndef ENEMY_FACTORY_HPP_
#define ENEMY_FACTORY_HPP_

#include "monsters.hpp"
#include <memory>

namespace Game
{
    class AbstractEnemyFactory
    {
    public:
        virtual std::unique_ptr<Enemy> CreateSoldier() = 0;
        virtual std::unique_ptr<Enemy> CreateMonster() = 0;
        virtual std::unique_ptr<Enemy> CreateSuperMonster() = 0;
        virtual ~AbstractEnemyFactory() = default;
    };

    class EasyLevelEnemyFactory : public AbstractEnemyFactory
    {
    public:
        std::unique_ptr<Enemy> CreateSoldier() override
        {
            return std::make_unique<SillySoldier>();
        }

        std::unique_ptr<Enemy> CreateMonster() override
        {
            return std::make_unique<SillyMonster>();
        }

        std::unique_ptr<Enemy> CreateSuperMonster() override
        {
            return std::make_unique<SillySuperMonster>();
        }
    };

    class DieHardLevelEnemyFactory : public AbstractEnemyFactory
    {
    public:
        std::unique_ptr<Enemy> CreateSoldier() override
        {
            return std::make_unique<BadSoldier>();
        }

        std::unique_ptr<Enemy> CreateMonster() override
        {
            return std::make_unique<BadMonster>();
        }

        std::unique_ptr<Enemy> CreateSuperMonster() override
        {
            return std::make_unique<BadSuperMonster>();
        }
    };
}

#endif /*ENEMY_FACTORY_HPP_*/
