#ifndef FT_FIGHT
#define FT_FIGHT

#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>

#include "ft_creatures.hpp"
#include "ft_moves.hpp"

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::max;
using std::min;
using std::unique_ptr;
using std::make_unique;
using std::endl;

bool start_fight(Player& player){
    int selected_move;
    int selected_target;

    // GENERATE ENEMIES
    vector<unique_ptr<Creature>> enemies;
    
    int enemy_count = (rand() % 3);
    for (int n = 0; n < enemy_count; n++){
        if ((rand() % 3) == 2){
            enemies.push_back(make_unique<DiscoDevil>("Dan"));
        }
        else{
            enemies.push_back(make_unique<GrooveGoblin>("Gary"));
        }
    }
    // ANNOUNCE FIGHT
    cout << "--------- A FIGHT HAS STARTED! ---------" << endl;
    cout << "You encounter " << enemies.size() << " dancers!" << endl;
    for(const auto& enemy : enemies){
        cout << enemy->get_name() << endl;
    }

    // RUN FIGHT
    while (player.get_health() > 0){
        cout << player.list_moves();
        cout << "Select move: ";
        cin >> selected_move;

        cout << "Select target: ";
        cin >> selected_target;

        cout << player.target(*enemies[selected_target-1], selected_move-1);


        
    }


    // RETURN RESULTS
    

    return false;
}





#endif