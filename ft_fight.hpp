#ifndef FT_FIGHT
#define FT_FIGHT

#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>

#include "ft_creatures.hpp"
#include "ft_moves.hpp"
#include "ft_drawer.hpp"

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
    string buffer;
    string message = "";

    // GENERATE ENEMIES
    vector<unique_ptr<Creature>> enemies;
    
    int enemy_count = (rand() % 3);
    for (int n = 0; n <= enemy_count; n++){
        if ((rand() % 3) == 2){
            enemies.push_back(make_unique<DiscoDevil>());
        }
        else{
            enemies.push_back(make_unique<GrooveGoblin>());
        }
    }
    // ANNOUNCE FIGHT
    counter = 1;
    message = "";
    message += "A FIGHT HAS STARTED!\n\n";
    message += "You encounter " + to_string(enemies.size()) + " dancers!\n\n";
    for(const auto& enemy : enemies){
        message += to_string(counter) + ". " + enemy->get_name() + "\n";
        counter++;
    }


    // RUN FIGHT
    while (player.get_health() > 0){
        message += "\nPress ENTER to continue!";
        battle_state(player, message, enemies);
        cin.ignore();
        getline(cin, buffer);
        
        // counter = 1;
        // cout << "-------------------- ENEMY STATUS --------------------" << endl;
        // for(const auto& enemy : enemies){
        //     cout << to_string(counter) << ".  HP: " << to_string(enemy->get_health()) << "\t" << enemy->get_name() << endl;
        //     counter++;
        // }
        // cout << endl;

        // cout << "------------------- PLAYER STATUS! -------------------" << endl;
        // cout << player.get_name() << "\tHP: " << to_string(player.get_health()) << "   ENG: "  
        //     << to_string(player.get_energy()) << "/" << to_string(player.get_max_energy()) << endl;
        // cout << endl;

        message += "SELECT YOUR MOVE!\n\n";
        selected_move = -1;
        bool valid = false;
        while (!valid){
            valid = true;
            message += player.list_moves_advanced();
            message += "\nType in the number of the move you want to use\n\n";
            battle_state(player, message, enemies);
            cin >> selected_move;
            if (selected_move < 1 || selected_move > static_cast<int>(player.known_moves.size())){
                message += "INVALID MOVE, PLEASE CHOOSE ANOTHER\n\n";
                valid = false;
            }
            else if (player.known_moves[selected_move-1]->get_cost() > player.get_energy()){
                message += "NOT ENOUGH ENERGY FOR THIS MOVE :(\n\n";
                valid = false;
            }
        }

        // SELECT TARGET
        selected_target = -1;

        if (player.known_moves[selected_move-1]->has_targets()){
            while (selected_target < 1 || selected_target > static_cast<int>(enemies.size())){
                message += "Select target: \n\n";
                counter = 1;
                for(const auto& enemy : enemies){
                    message += to_string(counter) + ". " + enemy->get_name() + "\n";
                    counter++;
                }
                battle_state(player, message, enemies);
                cin >> selected_target;
                if (selected_target < 1 || selected_target > static_cast<int>(enemies.size())){
                    message += "INVALID TARGET, PLEASE CHOOSE ANOTHER\n\n";
                }
            }

            // DO MOVE
            message += player.target(*enemies[selected_target-1], selected_move-1) + "\n\n";

        }
        // DO MOVE IF NOT TARGETED
        else {
            message += player.target(selected_move-1) + "\n\n";
        }

        counter = 0;
        // CHECK IF ENEMIES DIED
        for (auto enemy = enemies.begin(); enemy != enemies.end();) {
            if ((*enemy)->get_health() <= 0) {
                message += (*enemy)->get_name() + " has been OUT FUNKED!\n";
                enemy = enemies.erase(enemy);
            } else {
                enemy++;
            }
        }

        message += "\n";

        // CHECK IF ALL ENEMIES DEAD
        if (enemies.size() == 0){
            message += "You have out funked your enemies!\n";
            message += "GROOVE ON BY PRESSING ENTER\n";
            battle_state(player, message, enemies);
            cin.ignore();
            getline(cin, buffer);
            return true;
        }

        // ENEMIES ATTACK
        for(const auto& enemy : enemies){
            message += enemy->target(player) + "\n";
            if (player.get_health() == 0){
                message += player.get_name() + " has been OUT FUNKED!\n\n";
                message += "YOU HAVE LOST YOUR GROOVE, GET OFF THE STAGE BY PRESSING ENTER\n";
                battle_state(player, message, enemies);
                cin.ignore();
                getline(cin, buffer);
                return false;
            }
        }
        
    }


    // RETURN RESULTS
    

    return false;
}





#endif