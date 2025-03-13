#ifndef FT_DRAWER
#define FT_DRAWER

#if defined(__linux__)
    #define CLEAR_COMMAND "clear";
#elif __linux__
    #define CLEAR_COMMAND "clear";
#elif __APPLE__
    #define CLEAR_COMMAND "clear"
#elif _WIN32
    #define CLEAR_COMMAND "cls";
#elif _WIN64
    #define CLEAR_COMMAND "cls";
#endif

#include <stdlib.h>
#include <iostream>
#include <sstream> 

// MY HEADERS
#include "ft_sprites.hpp"
#include "ft_creatures.hpp"

// INTERNET HEADERS
#include "termcolor.hpp"

using std::cout;
using std::cin;
using std::stringstream;
using std::getline;

string sprite_combine(string left_sprite, string right_sprite){
    // ASSUMES EQUAL LINE COUNT
    string return_str = "";
    stringstream left_stream(left_sprite);
    stringstream right_stream(right_sprite);

    while (getline(left_stream, left_sprite, '\n') && getline(right_stream, right_sprite, '\n')){
        return_str += left_sprite + right_sprite + '\n';
    }

    return return_str;
}

string pad_space(string my_str, int my_len){
    int spaces_to_add = my_len - static_cast<int>(my_str.length());
    for (int i = 0; i < spaces_to_add; i++){
        my_str += " ";
    }
    return my_str;
}

string pad_block(string my_string, int my_len, string start = "", string end = ""){
    string ret_str = "";
    stringstream str_stream(my_string);
    while (getline(str_stream, my_string, '\n')){
        ret_str += start + pad_space(my_string, my_len) + end + "\n";
    }
    return ret_str;
}

string wrap_string(string my_string, int wrap_width){
    string ret_str = "";
    string buffer = "";
    stringstream str_stream(my_string);
    while (getline(str_stream, my_string, '\n')){
        int string_size = static_cast<int>(my_string.size());
        for (int i = 0; i + wrap_width <= string_size; ){
            i += wrap_width;
            for (int n = i; n > i - wrap_width; n--)
                if (my_string[n] == ' '){
                    my_string.insert(n+1, "\n");
                    i -= (i - (n + 1));
                    break;
                }
        }
        ret_str += my_string + "\n"; 
    }
    return ret_str;
}

int count_lines(string my_string){
    int count = 0;
    stringstream str_stream(my_string);
    while (getline(str_stream, my_string, '\n')){
        count++;
    }
    return count;
}



string draw_player_hp(Creature& player, int bar_size){
    int squares_to_draw = (bar_size * player.get_health()) / player.get_max_health();
    string top = "╔═";
    string bot = "╚═";
    string middle = "";

    for (int i = 0; i < bar_size; i++){
        top += "═";
        bot += "═";
    }

    top += "═╗\n";
    bot += "═╝\n";

    for (int n = 0; n < squares_to_draw; n++){
        middle += "█";
    }
    for (int n = 0; n < (bar_size - squares_to_draw); n++){
        middle += " ";
    }

    //COLOR GREEN
    if (squares_to_draw > bar_size/2){
        middle = "\033[1;32m" + middle + "\033[0m";
    }

    //COLOR YELLOW
    else if (squares_to_draw <= bar_size/2 && squares_to_draw > bar_size/4){
        middle = "\033[1;33m" + middle + "\033[0m";
    }

    //COLOR RED
    else {
        middle = "\033[1;31m" + middle + "\033[0m";
    }

    middle = "║ " + middle + " ║\n";

    return top + middle + bot;
}

string draw_energy(Creature& player){
    int squares_to_draw = player.get_energy();
    string top = "╔═══════╦═══════╦═══════╦═══════╗\n";
    string bot = "╚═══════╩═══════╩═══════╩═══════╝\n";
    string middle = "";
    for (int n = 0; n < squares_to_draw; n++){
        middle += "║ \033[1;34m█████\033[0m "; //BLUE
    }
    for (int n = 0; n < (player.get_max_energy() - squares_to_draw); n++){
        middle += "║       ";
    }

    middle = middle + "║\n";

    return top + middle + bot;
}

string draw_enemy_health(vector<unique_ptr<Creature>>& enemies, int enemy_health_bar_size){
    int enemy_count = static_cast<int>(enemies.size());
    string enemy_health_bars;
    for (int i = 0; i < 3; i++){
        string filler = "";
        if (enemy_count > i){
            filler = draw_player_hp(*enemies[i], enemy_health_bar_size);
        }
        else{
            filler = ENEMY_NO_HEALTH;
        }
            if (i == 0){
                enemy_health_bars = sprite_combine(ENEMY_SIDE_L_SMALL, sprite_combine(filler, ENEMY_SPLIT_SMALL));
            }
            else if (i == 1){
                enemy_health_bars = sprite_combine(enemy_health_bars, sprite_combine(filler, ENEMY_SPLIT_SMALL));
            }
            else {
                enemy_health_bars = sprite_combine(enemy_health_bars, sprite_combine(filler, ENEMY_SIDE_R_SMALL));
            }
        }
    return enemy_health_bars;
}

string draw_enemy_names(vector<unique_ptr<Creature>>& enemies, int name_bar_size){
    int enemy_count = static_cast<int>(enemies.size());
    string enemy_names;
    for (int i = 0; i < 3; i++){
        string filler = "";
        if (enemy_count > i){
            filler = pad_space(enemies[i]->get_name(), name_bar_size);
        }
        else{
            filler = pad_space("", name_bar_size);
        }
            if (i == 0){
                enemy_names = sprite_combine(ENEMY_SIDE_L_LINE, sprite_combine(filler, ENEMY_SPLIT_LINE));
            }
            else if (i == 1){
                enemy_names = sprite_combine(enemy_names, sprite_combine(filler, ENEMY_SPLIT_LINE));
            }
            else {
                enemy_names = sprite_combine(enemy_names, sprite_combine(filler, ENEMY_SIDE_R_LINE));
            }
        }
    return enemy_names;
}

string draw_enemy_sprites(vector<unique_ptr<Creature>>& enemies){
    int enemy_count = static_cast<int>(enemies.size());
    string enemy_names;
    for (int i = 0; i < 3; i++){
        string filler = "";
        if (enemy_count > i){
            filler = enemies[i]->get_sprite();
        }
        else{
            filler = ENEMY_BOX_EMPTY;
        }
            if (i == 0){
                enemy_names = sprite_combine(ENEMY_SIDE_L, sprite_combine(filler, ENEMY_SPLIT));
            }
            else if (i == 1){
                enemy_names = sprite_combine(enemy_names, sprite_combine(filler, ENEMY_SPLIT));
            }
            else {
                enemy_names = sprite_combine(enemy_names, sprite_combine(filler, ENEMY_SIDE_R));
            }
        }
    return enemy_names;
}

void screen_size_test(){
    //TODO: IMPLEMENT
}

void title_screen(){
    system(CLEAR_COMMAND);
    cout << TITLE_TOP;
    cout << sprite_combine(sprite_combine(TITLE_WALL_L, TITLE), TITLE_WALL_R);
    cout << TITLE_BOT;


}

void battle_state(Creature& player, string& message, vector<unique_ptr<Creature>>& enemies){
    int right_data_width = 39;
    int left_data_width = 73;
    int left_data_height = 16;
    int player_health_bar_size = 34;
    int enemy_health_bar_size = 25;
    int enemy_name_bar_size = enemy_health_bar_size + 4;
    string health_string = to_string(player.get_health()) + "/" + to_string(player.get_max_health());
    string energy_string = to_string(player.get_energy()) + "/" + to_string(player.get_max_energy());
    system(CLEAR_COMMAND);
    string energy_bar_and_wall = sprite_combine("  \n  \n  \n", sprite_combine(draw_energy(player), "   ║\n   ║\n   ║\n"));
    string health_bar_and_wall = sprite_combine(draw_player_hp(player, player_health_bar_size), "║\n║\n║\n");
    string right_data_data = FIGHT_DATA_R_LINE
                            + pad_space("    " + player.get_name() + "'s stats", right_data_width-1) + "║\n"
                            + FIGHT_DATA_R_LINE 
                            + pad_space("    Strength: " + to_string(player.get_strength()), right_data_width-1) + "║\n"  
                            + FIGHT_DATA_R_LINE 
                            + pad_space("    Defense: " + to_string(player.get_defense()), right_data_width-1) + "║\n" 
                            + FIGHT_DATA_R_LINE
                            + pad_space(("    Health: " + health_string), right_data_width-1) + "║\n" 
                            + health_bar_and_wall 
                            + FIGHT_DATA_R_LINE 
                            + pad_space("    Energy: " + energy_string, right_data_width-1) + "║\n" 
                            + energy_bar_and_wall;

    string left_data_data = FIGHT_DATA_L_LINE
                            + pad_block(wrap_string(message, left_data_width-6), left_data_width-3, "║   ", "║")
                            + "";

    string enemy_health_bars = draw_enemy_health(enemies, enemy_health_bar_size);
    string enemy_names = draw_enemy_names(enemies, enemy_name_bar_size);
    string enemy_sprites = draw_enemy_sprites(enemies);

    int left_data_line_count = count_lines(left_data_data);
    for (int i = 0; i < left_data_height - left_data_line_count; i++){
        left_data_data += FIGHT_DATA_L_LINE;
    }

    cout << TITLE_TOP;
    cout << enemy_names;
    cout << enemy_sprites;
    cout << enemy_health_bars;
    cout << FIGHT_MIDDLE;
    cout << sprite_combine(left_data_data, right_data_data);
    cout << FIGHT_BOT;

    message = "";

}

#endif