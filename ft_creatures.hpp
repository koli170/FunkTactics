#ifndef FT_CREATURES
#define FT_CREATURES

#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>

#include "ft_sprites.hpp"

using std::string;
using std::vector;
using std::max;
using std::min;
using std::unique_ptr;
using std::make_unique;
using std::to_string;

string funkify(string name){
    // Adds a funky adjective to the start of the string, matches first letter
    switch(name[0]) {
        case 'A': case 'a': name = "Astral " + name; break;
        case 'B': case 'b': name = "Boogie " + name; break;
        case 'C': case 'c': name = "Cosmic " + name; break;
        case 'D': case 'd': name = "Disco " + name; break;
        case 'E': case 'e': name = "Electric " + name; break;
        case 'F': case 'f': name = "Funky " + name; break;
        case 'G': case 'g': name = "Groovy " + name; break;
        case 'H': case 'h': name = "Hotfoot " + name; break;
        case 'I': case 'i': name = "Indigo " + name; break;
        case 'J': case 'j': name = "Jazzy " + name; break;
        case 'K': case 'k': name = "Kickin' " + name; break;
        case 'L': case 'l': name = "Lo-fi " + name; break;
        case 'M': case 'm': name = "Melodic " + name; break;
        case 'N': case 'n': name = "Nautical " + name; break;
        case 'O': case 'o': name = "Omni " + name; break;
        case 'P': case 'p': name = "Phat " + name; break;
        case 'Q': case 'q': name = "Quick " + name; break;
        case 'R': case 'r': name = "Retro " + name; break;
        case 'S': case 's': name = "Slick " + name; break;
        case 'T': case 't': name = "Turbo " + name; break;
        case 'U': case 'u': name = "Ultra " + name; break;
        case 'V': case 'v': name = "Vinyl " + name; break;
        case 'W': case 'w': name = "Whammy  " + name; break;
        case 'X': case 'x': name = "Xenon " + name; break;
        case 'Y': case 'y': name = "Yippee " + name; break;
        case 'Z': case 'z': name = "Zesty " + name; break;
    }
    return name;
}

struct Creature {
    /*
    Base class for all creatures:

    Variables
        string name, the name of the creatures
        int max_health, the maximum health value of the creature
        int curr_health, the current health value of the creature
        int max_energy, the maximum energy value of the creature
        int curr_energy, the current energy value of the creature
        int defense, the defense value of the creature
        int strength, the strength value of the creature
        string sprite, the sprite of the creature

    Functions
        Base constructor
        int get_health(), returns the current health value of the creature
        int get_max_health(), returns the maximum health value of the creature
        int get_energy(), returns the current energy value of the creature
        int get_maximum_energy(), returns the maximum energy value of the creature
        int get_defense(), returns the defense value of the creature
        int get_strength(), returns the strength value of the creature
        string get_name(), returns the name of the creature
        string get_sprite(), returns the sprite of the creature
        string target(int selected_move), targets itself with a move at index in its known_moves
        string target(Creature& victim), targets a creature without specifying move, 
                                        used for enemies since they use random moves
        string target(Creature& victim, int selected_move), targets a creatue with a move at index in its known_moves
        void modify_health(int value), adds the given value to the current health of the creature,
                                        current health is always between 0 and max_health
        void modify_energy(int value), adds the given value to the current energy of the creature,
                                        current energy is always between 0 and max_energy
    */
    protected:
        string name;
        int max_health;
        int curr_health;
        int max_energy;
        int curr_energy;
        int defense;
        int strength;
        string sprite;

        Creature(string name, int health_base = 0, int defense = 10, int strength = 10, int energy = 4, string sprite = ENEMY_BOX_EMPTY) : 
            name{name}, 
            max_health{health_base}, 
            curr_health{max_health}, 
            max_energy{energy}, 
            curr_energy{0}, 
            defense{defense}, 
            strength{strength},
            sprite{sprite}
        {}


    
    public:

        int get_health(){
            return curr_health;
        }
        
        int get_max_health(){
            return max_health;
        }

        int get_energy(){
            return curr_energy;
        }

        int get_max_energy(){
            return max_energy;
        }

        int get_defense(){
            return defense;
        }

        int get_strength(){
            return strength;
        }

        string get_name(){
            return name;
        }
        
        string get_sprite(){
            return sprite;
        }

        virtual ~Creature() = default;
        virtual string target(int selected_move){
            return this->get_name() + " uses move " + to_string(selected_move);
        }
        virtual string target(Creature& victim){
            return this->get_name() + " targets " + victim.get_name();
        }
        virtual string target(Creature& victim, int selected_move){
            return this->get_name() + " targets " + victim.get_name() + " with " + to_string(selected_move);
        }

        void modify_health(int value){
            curr_health += value;
            curr_health = max(0, min(curr_health, max_health));
        }

        void modify_energy(int value){
            curr_energy += value;
            curr_energy = max(0, min(curr_energy, max_energy));
        }
    
};

// INCLUDED HERE TO AVOID CIRCULAR DEPENDENCIES
// Move only needs to referance the base class of creature, so creature is defined before moves.
#include "ft_moves.hpp"


struct Player : Creature {
    /*
    The class for the player creature, this is a representation of the players character

    Variables
        int health, health value of the player
        int defense, defense value of the player
        int strength, strength value of the player
        vector<unique_ptr<Move>> known_moves, a vector containing the moves that the player knows

    Functions
        Basic constructor
        string list_moves(), returns a string of the moves the player knows, numbered
        string list_moves_advanced(), returns a similar string to list_moves(), but with added stats of the moves
        string target(int move_number), uses a move without targets, returns a string of what the move did
        string target(Creature& victim, int move_number) uses a move with targets, returns a string of what the move did


    */
    protected:
        static constexpr int health = 100;
        static constexpr int defense = 40;
        static constexpr int strength = 20;
    public:
        vector<unique_ptr<Move>> known_moves;
        Player(string name) : Creature{funkify(name), health, defense, strength}
        {
            //MOVES KNOWN AT START
            known_moves.push_back(make_unique<JazzHands>());
            known_moves.push_back(make_unique<Macarena>());
            known_moves.push_back(make_unique<PumpUp>());
            known_moves.push_back(make_unique<TakeFive>());
            
        }

        string list_moves(){
            int count = 1;
            string ret_str = "";
            for (const auto& move : known_moves){
                ret_str += (to_string(count) + ". " + move->get_name() + "\n");
                count++;
            }
            return ret_str;
        }

        string list_moves_advanced(){
            int count = 1;
            string ret_str = "";
            for (const auto& move : known_moves){
                ret_str += (to_string(count) + ". " + move->get_stats() + "\n");
                count++;
            }
            return ret_str;
        }
        string target(int move_number){
            if (known_moves.size() <= 0){ 
                return "No moves";
            }
            if (move_number < 0 || move_number > static_cast<int>(known_moves.size())){
                return "Invalid move";
            }
            return known_moves[move_number]->target(*this);
        }

        string target(Creature& victim, int move_number){
            if (known_moves.size() <= 0){ 
                return "No moves";
            }
            if (move_number < 0 || move_number > static_cast<int>(known_moves.size())){
                return "Invalid move";
            }
            return known_moves[move_number]->target(*this, victim);
        }

    
};


struct Enemy : Creature {
    /*
    Base class for enemy creatures

    Variables
        vector<unique_ptr<Move>> known_moves, a vector containing the moves that the enemey knows

    Functions
        Basic constructor
        string target(Creature& victim), chooses a random move that the enemy knows and uses, move is cast on victim if targeted

    */
    protected:
        //Constructor takes in an additional h_extra variable for the random extra health an enemy can have
        Enemy(string name, int h_base, int h_extra, int strength, int defense, string sprite) : 
            Creature{name, h_base + (rand() % h_extra), defense, strength, 4, sprite}
        {}

    public:
        vector<unique_ptr<Move>> known_moves;
        string target(Creature& victim){
            if (known_moves.size() > 0){
                bool valid_move = false;
                int selected_move;
                while (!valid_move){
                    selected_move = rand() % static_cast<int>(known_moves.size());
                    if (known_moves[selected_move]->get_cost() <= get_energy()){
                        valid_move = true;
                    }
                }
                if (known_moves[selected_move]->has_targets()){
                    return known_moves[selected_move]->target(*this, victim);
                }
                return known_moves[selected_move]->target(*this);
            }
            return "No moves";
        }
};


struct GrooveGoblin : Enemy {
    /*
    The basic grunt enemy, with subpar stats and only some basic moves
    Design to be easy, but still pose a small threat when in larger groups
    */
    protected:
        static constexpr int health_base = 50;
        static constexpr int health_extra = 20;
        static constexpr int strength = 5;
        static constexpr int defense = 5;
        static const vector<string> name_list;
        static const string sprite;
    public:
        GrooveGoblin() : Enemy{"Groove Goblin " + name_list[rand() % name_list.size()], health_base, health_extra, strength, defense, sprite}
        {
            // Known moves at start
            known_moves.push_back(make_unique<JazzHands>());
            known_moves.push_back(make_unique<Macarena>());
        }
};

// The string of names, one is chosen at random on enemy creation.
const vector<string> GrooveGoblin::name_list = {"Gary", "Guppy", "Grumpy", "Grechen", "Gumbi", "Giuseppe", "Gunther", "Gorganthal"};
// The sprite for the enemy
const string GrooveGoblin::sprite = GROOVE_GOBLIN_SPRITE;

struct DiscoDevil : Enemy {
    protected:
        static constexpr int health_base = 90;
        static constexpr int health_extra = 40;
        static constexpr int strength = 15;
        static constexpr int defense = 20;
        static const vector<string> name_list;
        static const string sprite;
    public:
        DiscoDevil() : Enemy{"Disco Devil " + name_list[rand() % name_list.size()], health_base, health_extra, strength, defense, sprite}
        {
            // Known moves at start
            known_moves.push_back(make_unique<JazzHands>());
            known_moves.push_back(make_unique<Macarena>());
            known_moves.push_back(make_unique<PumpUp>());
            known_moves.push_back(make_unique<TakeFive>());
        }
};

// The string of names, one is chosen at random on enemy creation.
const vector<string> DiscoDevil::name_list = {"Dan", "Darmacklemoore", "Darnell", "Dizzy", "Daraxxus"};
// The sprite for the enemy
const string DiscoDevil::sprite = DISCO_DEVIL_SPRITE;

struct BustdownBomber : Enemy {
    protected:
        static constexpr int health_base = 110;
        static constexpr int health_extra = 60;
        static constexpr int strength = 25;
        static constexpr int defense = 30;
        static const vector<string> name_list;
        static const string sprite;
    public:
        BustdownBomber() : Enemy{"Bustdown Bomber " + name_list[rand() % name_list.size()], health_base, health_extra, strength, defense, sprite}
        {
            // Known moves at start
            known_moves.push_back(make_unique<Tick>());
            known_moves.push_back(make_unique<MLBustdown>());
        }
};

// The string of names, one is chosen at random on enemy creation.
const vector<string> BustdownBomber::name_list = {"Bill", "Bob", "Bartholomew", "Barry", "Burgundy"};
// The sprite for the enemy
const string BustdownBomber::sprite = BUSTDOWN_BOMBER_SPRITE;


#endif