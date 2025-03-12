#include <iostream>

#include "ft_creatures.hpp"
#include "ft_moves.hpp"
#include "ft_fight.hpp"
#include "ft_drawer.hpp"

using namespace std;


int main() {
    std::srand(std::time({}));

    GrooveGoblin kyle = GrooveGoblin();
    GrooveGoblin dave = GrooveGoblin();
    DiscoDevil cora = DiscoDevil();
    DiscoDevil tar = DiscoDevil();

    string player_name;

    JazzHands jh = JazzHands();

    screen_size_test();
    title_screen();

    cout << "Input name: ";
    cin >> player_name;
    Player pl = Player(player_name);

    battle_state(pl);

    cout << start_fight(pl);

    

    return 0;
}