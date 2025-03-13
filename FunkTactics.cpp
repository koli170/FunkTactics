#include <iostream>

#include "ft_creatures.hpp"
#include "ft_moves.hpp"
#include "ft_fight.hpp"
#include "ft_drawer.hpp"

using namespace std;


int main() {
    std::srand(std::time({}));

    string player_name;

    int fight_amount = 3;
    bool win = false;

    title_screen();

    cout << "Input name: ";
    getline(cin, player_name);

    while (static_cast<int>(player_name.size()) > 15){
        cout << "Please make sure the name is 15 characters or less: ";
        getline(cin, player_name);
    }

    Player pl = Player(player_name);

    for (int i = 0; i < fight_amount; i++){
        win = start_fight(pl);
        if (!win){
            game_over();
            break;
        }
    }

    if (win){
        victory();
    }
    

    return 0;
}