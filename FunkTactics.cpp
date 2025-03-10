#include <iostream>

#include "ft_creatures.hpp"
#include "ft_moves.hpp"
#include "ft_fight.hpp"

using namespace std;


int main() {
    std::srand(std::time({}));

    GrooveGoblin kyle = GrooveGoblin("Kyle");
    GrooveGoblin dave = GrooveGoblin("Dave");
    DiscoDevil cora = DiscoDevil("Coraxxus, Eater of All");
    DiscoDevil tar = DiscoDevil("Tarmacklemoore, Singer of Wonderwall");

    string player_name;
    cout << "Input name: ";
    cin >> player_name;
    Player pl = Player(player_name);

    JazzHands jh = JazzHands();

    cout << start_fight(pl);

    

    return 0;
}