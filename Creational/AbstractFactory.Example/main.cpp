#include "game.hpp"

using namespace std;
using namespace Game;

int main()
{
    random_device rd{};
    auto rnd_gen = std::mt19937{rd()};

    GameApp game{ rnd_gen };
    game.select_level(GameLevel::easy);
    game.play();

    cout << "\n\n";

    game.select_level(GameLevel::die_hard);    
    game.play();
}
