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

struct Creature {
    protected:
        string name;
        int max_health;
        int curr_health;
        int max_energy;
        int curr_energy;
        int speed;
        int defense;

        Creature(string name, int health_base = 0, int energy = 4, int speed = 5, int defense = 10)
            : name{name}, max_health{health_base}, curr_health{max_health}, max_energy{energy}, curr_energy{max_energy}, speed{speed}, defense{defense}
        {}


    
    public:
        int get_health(){
            return curr_health;
        }

        int get_energy(){
            return curr_energy;
        }

        int get_speed(){
            return speed;
        }

        int get_defense(){
            return defense;
        }
        string get_name(){
            return name;
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
        static constexpr int moves_count = 2;
        vector<unique_ptr<Move>> known_moves;
    public:
        Player(string name) : Creature{"Player " + name, 100}
        {
            known_moves.push_back(make_unique<JazzHands>());
            known_moves.push_back(make_unique<Macarena>());
        }

        string list_moves(){
            int count = 1;
            string ret_str = "";
            for (const auto& move : known_moves){
                ret_str += (to_string(count) + ". " + move->get_name() + "\n");
            }
            return ret_str;
        }

        string target(Creature& victim, int move_number){
            if (moves_count <= 0){ 
                return "No moves";
            }
            if (move_number < 0 || move_number >= moves_count){
                return "Invalid move";
            }
            return known_moves[move_number]->target(*this, victim);
        }

    
};


struct Enemy : Creature {
    protected:
        int moves_count;
        vector<unique_ptr<Move>> known_moves;
        Enemy(string name, int h_base, int h_extra, int moves_count = 0) : 
            Creature{name, h_base + (rand() % h_extra)}, moves_count{moves_count}
        {}

    public:
        string target(Creature& victim){
            if (moves_count > 0){ 
                return known_moves[rand() % moves_count]->target(*this, victim);
            }
            return "No moves";
        }
};


struct GrooveGoblin : Enemy {
    protected:
        static constexpr int health_base = 50;
        static constexpr int health_extra = 20;
        static constexpr int moves_count = 2;
    public:
        GrooveGoblin(string name) : Enemy{"Groove Goblin " + name, health_base, health_extra, moves_count}
        {
            known_moves.push_back(make_unique<JazzHands>());
            known_moves.push_back(make_unique<Macarena>());
        }
};

struct DiscoDevil : Enemy {
    protected:
        static constexpr int health_base = 80;
        static constexpr int health_extra = 40;
        static constexpr int moves_count = 1;
    public:
        DiscoDevil(string name) : Enemy{"Disco Devil " + name, health_base, health_extra, moves_count}
        {
            known_moves.push_back(make_unique<JazzHands>());
        }
};

#endif