#ifndef GAME_HPP_
#define GAME_HPP_

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "enemy_factory.hpp"

namespace Game
{
    enum class GameLevel
    {
        easy,
        die_hard
    };

    class GameApp
    {
        std::vector<std::unique_ptr<Enemy>> enemies_;
        std::unique_ptr<EnemyFactory> enemy_factory_;
        std::mt19937 rnd_gen_;

    public:
        GameApp(const std::mt19937& rnd_gen)
            : rnd_gen_{rnd_gen}
        {
        }

        virtual ~GameApp() = default;

        GameApp(const GameApp&) = delete;
        GameApp& operator=(const GameApp&) = delete;

        void select_level(GameLevel level)
        {
            switch (level)
            {
            case GameLevel::easy:
                enemy_factory_ = std::make_unique<EasyLevelEnemyFactory>();
                break;
            case GameLevel::die_hard:
                enemy_factory_ = std::make_unique<DieHardLevelEnemyFactory>();
                break;
            }
        }

        void play()
        {
            init_game(12);
            fight();
            show_score();
        }

    protected:
        virtual void init_game(int number_of_enemies)
        {
            assert(enemy_factory_ != nullptr);
            enemies_.clear();

            std::uniform_int_distribution<> distr(0, 100);

            for (int i = 0; i < number_of_enemies; ++i)
            {
                auto rnd_value = distr(rnd_gen_);
                if (rnd_value < 40)
                    enemies_.push_back(enemy_factory_->CreateSoldier());
                else if (rnd_value > 70)
                    enemies_.push_back(enemy_factory_->CreateMonster());
                else
                    enemies_.push_back(enemy_factory_->CreateSuperMonster());
            }
        }

        virtual void fight()
        {
            for (const auto& e : enemies_)
                e->action();
        }

        virtual void show_score()
        {
        }
    };
}
#endif /*GAME_HPP_*/
