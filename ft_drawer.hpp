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

string draw_player_hp(Creature& player){
    int square_amount = 34; // Amount of squares that fit in the bar
    int squares_to_draw = (square_amount * player.get_health()) / player.get_max_health();
    string top = "╔════════════════════════════════════╗\n";
    string bot = "╚════════════════════════════════════╝\n";
    string middle = "";
    for (int n = 0; n < squares_to_draw; n++){
        middle += "█";
    }
    for (int n = 0; n < (square_amount - squares_to_draw); n++){
        middle += " ";
    }

    //COLOR GREEN
    if (squares_to_draw > square_amount/2){
        middle = "\033[1;32m" + middle + "\033[0m";
    }

    //COLOR YELLOW
    else if (squares_to_draw <= square_amount/2 && squares_to_draw > square_amount/4){
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

void screen_size_test(){
    //TODO: IMPLEMENT
}

void title_screen(){
    system(CLEAR_COMMAND);
    cout << TITLE_TOP;
    cout << sprite_combine(sprite_combine(TITLE_WALL_L, TITLE), TITLE_WALL_R);
    cout << TITLE_BOT;


}

void battle_state(Creature& player){
    int right_data_width = 39;
    string health_string = to_string(player.get_health()) + "/" + to_string(player.get_max_health());
    string energy_string = to_string(player.get_energy()) + "/" + to_string(player.get_max_energy());
    system(CLEAR_COMMAND);
    string energy_bar_and_wall = sprite_combine("  \n  \n  \n", sprite_combine(draw_energy(player), "   ║\n   ║\n   ║\n"));
    string health_bar_and_wall = sprite_combine(draw_player_hp(player), "║\n║\n║\n");
    cout << TITLE_TOP;
    cout << sprite_combine(sprite_combine(sprite_combine(sprite_combine(sprite_combine(sprite_combine(ENEMY_SIDE_L, ENEMY_TEST_BOX), ENEMY_SPLIT), ENEMY_TEST_BOX), ENEMY_SPLIT), ENEMY_TEST_BOX), ENEMY_SIDE_R);
    cout << FIGHT_MIDDLE;
    cout << sprite_combine(FIGHT_DATA_L, FIGHT_DATA_R_FILL + pad_space(("    Health: " + health_string), right_data_width-1) + "║\n" 
        + health_bar_and_wall + pad_space("    Energy: " + energy_string, right_data_width-1) + "║\n" + energy_bar_and_wall);
    cout << FIGHT_BOT;

}

#endif