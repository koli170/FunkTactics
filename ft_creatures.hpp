#ifndef FT_CREATURES
#define FT_CREATURES

#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>


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
    protected:
        string name;
        int max_health;
        int curr_health;
        int max_energy;
        int curr_energy;
        int speed;
        int defense;
        int strength;

        Creature(string name, int health_base = 0, int defense = 10, int strength = 10, int energy = 4, int speed = 5)
            : name{name}, max_health{health_base}, curr_health{max_health}, max_energy{energy}, curr_energy{0}, speed{speed}, defense{defense}, strength{strength}
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

        int get_speed(){
            return speed;
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

        friend std::ostream& operator<<(std::ostream& outs, const Creature& creature);
    
};

#include "ft_moves.hpp"

std::ostream& operator<<(std::ostream& outs, const Creature& creature) {
    return outs << creature.name << ", " << creature.curr_health;
}


struct Player : Creature {
    protected:
        static constexpr int health = 100;
        static constexpr int defense = 30;
        static constexpr int strength = 20;
    public:
        vector<unique_ptr<Move>> known_moves;
        Player(string name) : Creature{funkify(name), health, defense, strength}
        {
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
    protected:
        Enemy(string name, int h_base, int h_extra, int strength, int defense) : 
            Creature{name, h_base + (rand() % h_extra), defense, strength}
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
    protected:
        static constexpr int health_base = 50;
        static constexpr int health_extra = 20;
        static constexpr int strength = 5;
        static constexpr int defense = 5;
        static const vector<string> name_list;
    public:
        GrooveGoblin() : Enemy{"Groove Goblin " + name_list[rand() % name_list.size()], health_base, health_extra, strength, defense}
        {
            known_moves.push_back(make_unique<JazzHands>());
            known_moves.push_back(make_unique<Macarena>());
        }
};

const vector<string> GrooveGoblin::name_list = {"Gary", "Guppy", "Grumpy", "Grechen", "Gumbi", "Giuseppe", "Gunther"};

struct DiscoDevil : Enemy {
    protected:
        static constexpr int health_base = 80;
        static constexpr int health_extra = 40;
        static constexpr int strength = 15;
        static constexpr int defense = 20;
        static const vector<string> name_list;
    public:
        DiscoDevil() : Enemy{"Disco Devil " + name_list[rand() % name_list.size()], health_base, health_extra, strength, defense}
        {
            known_moves.push_back(make_unique<JazzHands>());
            known_moves.push_back(make_unique<Macarena>());
            known_moves.push_back(make_unique<PumpUp>());
            known_moves.push_back(make_unique<TakeFive>());
        }
};

const vector<string> DiscoDevil::name_list = {"Dan", "Darmacklemoore", "Darnell", "Dizzy", "Daraxxus"};

#endif