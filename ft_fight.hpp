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
    int counter;

    // GENERATE ENEMIES
    vector<unique_ptr<Creature>> enemies;
    
    int enemy_count = (rand() % 3);
    for (int n = 0; n <= enemy_count; n++){
        if ((rand() % 3) == 2){
            enemies.push_back(make_unique<DiscoDevil>("Dan"));
        }
        else{
            enemies.push_back(make_unique<GrooveGoblin>("Gary"));
        }
    }
    // ANNOUNCE FIGHT
    counter = 1;
    cout << "--------- A FIGHT HAS STARTED! ---------" << endl;
    cout << "You encounter " << enemies.size() << " dancers!" << endl;
    for(const auto& enemy : enemies){
        cout << to_string(counter) << ". " << enemy->get_name() << endl;
        counter++;
    }
    cout << endl;

    // RUN FIGHT
    while (player.get_health() > 0){
        counter = 1;
        cout << "------------- ENEMY STATUS -------------" << endl;
        for(const auto& enemy : enemies){
            cout << to_string(counter) << ". " << enemy->get_name() << "\tHP: " << to_string(enemy->get_health()) << endl;
            counter++;
        }
        cout << endl;

        cout << "------------ PLAYER STATUS! ------------" << endl;
        cout << player.get_name() << "\tHP: " << to_string(player.get_health()) << "   ENG: "  << to_string(player.get_energy()) << "/" << to_string(player.get_max_energy()) << endl;
        cout << endl;

        cout << "------------- SELECT MOVE! -------------" << endl;
        selected_move = -1;
        while (selected_move < 1 || selected_move > player.get_move_count()){
            cout << player.list_moves_advanced();
            cout << "Select move: ";
            cin >> selected_move;
            if (selected_move < 1 || selected_move > player.get_move_count()){
                cout << "Invalid Move" << endl << endl;
            }
        }

        selected_target = -1;
        while (selected_target < 1 || selected_target > static_cast<int>(enemies.size())){
            cout << "Select target: ";
            cin >> selected_target;
            if (selected_target < 1 || selected_target > static_cast<int>(enemies.size())){
                cout << "Invalid Target" << endl << endl;
            }
        }
        cout << endl;

        cout << player.target(*enemies[selected_target-1], selected_move-1) << endl;

        counter = 0;
        for (auto enemy = enemies.begin(); enemy != enemies.end();) {
            if ((*enemy)->get_health() <= 0) {
                cout << (*enemy)->get_name() << " has been \033[1;31mOUT FUNKED!\033[0m" << endl;
                enemy = enemies.erase(enemy);
            } else {
                enemy++;
            }
        }

        cout << endl;

        if (enemies.size() == 0){
            return true;
        }

        for(const auto& enemy : enemies){
            cout << enemy->target(player) << endl;
            if (player.get_health() == 0){
                return false;
            }
        }
        cout << endl;

        
    }


    // RETURN RESULTS
    

    return false;
}





#endif