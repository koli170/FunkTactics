#ifndef FT_MOVES
#define FT_MOVES

#include <stdlib.h>
#include <string>

#include "ft_creatures.hpp"

using std::string;

struct Move {
    protected:
        string name;
        int cost;

    public:
        Move(string name, int cost = 0) : name{name}, cost{cost}
        {}
        virtual ~Move() = default;
        virtual string target(Creature& attacker, Creature& victim){
            return attacker.get_name() + " targets " + victim.get_name();;
        }
        
        virtual string get_stats(){
            return name + to_string(cost);
        }

        string get_name(){
            return name;
        }

        int get_cost(){
            return cost;
        }
    
};

struct Attack : Move {
    protected:
        const int CRIT_CHANCE = 10;
        int damage;
        int accuracy;
        int dealt;
        int cost;
        string ret_str = "";

    public:
        Attack(string name, int dmg, int accuracy = 100, int cst = 0) : Move{name, cst}, damage{dmg}, accuracy{accuracy}, cost{cst}
        {}

        string target(Creature& attacker, Creature& victim){
            ret_str = "";

            if ((rand() % 100)+1 > accuracy){
                return attacker.get_name() + " uses " + name + " on " + victim.get_name() + " and MISSES!";
            }

            if (cost == 0){
                attacker.modify_energy(1);
            }
            else {
                attacker.modify_energy(-cost);
            }
            if (rand() % CRIT_CHANCE == 0){
                dealt = damage * 2;
                ret_str += "CRIT! ";
            }
            else{
                dealt = damage + (rand() % (damage/3));
                dealt = (dealt*(100-victim.get_defense()))/100;
            }

            victim.modify_health(-dealt);
            ret_str = ret_str + attacker.get_name() + " uses " + name + " on " + victim.get_name() + " dealing " + std::to_string(dealt) + " damage!";

            return ret_str;
        };

        string get_stats(){
            return name + "\tPWR: " + to_string(damage) + "   ACC: " + to_string(accuracy) + "   CST: " + to_string(cost);
        }



};

struct JazzHands : Attack {
    protected:
        static constexpr int damage = 20;
        static constexpr int acc = 90;
        static inline string name = "Jazz Hands";
    
    public:
        JazzHands(string title = name, int dmg = damage, int accuracy = acc) : Attack{title, dmg, accuracy}
        {}
};

struct Macarena : Attack {
    protected:
        static constexpr int damage = 60;
        static constexpr int acc = 75;
        static constexpr int cost = 2;
        static inline string name = "Macarena";
    
    public:
        Macarena(string title = name, int dmg = damage, int accuracy = acc, int cst = cost) : Attack{title, dmg, accuracy, cst}
        {}
};


#endif