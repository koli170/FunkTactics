#ifndef FT_MOVES
#define FT_MOVES

#include <stdlib.h>
#include <string>

#include "ft_creatures.hpp"

using std::string;

struct Move {
    protected:
        string name;
        int power;
        int cost;
        int accuracy;
        bool targets = false;

    public:
        Move(string name, int cost = 0, int pwr = 10, int acc = 100, bool trgts = false) : name{name}, power{pwr}, cost{cost}, accuracy{acc}, targets{trgts}
        {}
        
        virtual ~Move() = default;

        string target(Creature& attacker, Creature& victim){
            string ret_str = "";
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

            return trigger(attacker, victim);
        };

        string target(Creature& attacker){
            string ret_str = "";
            ret_str = "";
    
            if ((rand() % 100)+1 > accuracy){
                return attacker.get_name() + " uses " + name + " and MISSES!";
            }

            if (cost == 0){
                attacker.modify_energy(1);
            }                
            else {
                attacker.modify_energy(-cost);
            }
    
            return trigger(attacker);
        }

        virtual string trigger(Creature& attacker, Creature& victim){
            return "Empty Trigger with " + attacker.get_name() + " and " + victim.get_name();
        }

        virtual string trigger(Creature& attacker){
            return "Empty Trigger with " + attacker.get_name();
        }

        string get_stats(){
            return name + "\tPWR: " + to_string(power) + "   ACC: " + to_string(accuracy) + "   CST: " + to_string(cost);
        }

        string get_name(){
            return name;
        }

        int get_cost(){
            return cost;
        }

        bool has_targets(){
            return targets;
        }
};

struct Stat : Move {
    protected:
        int power;
        int accuracy;
        int cost;
        bool targets = false;

    public:
        Stat(string name, int pwr, int acc = 100, int cst = 0) : Move{name, cst}, power{pwr}, accuracy{acc}, cost{cst}
        {}

        string target(Creature& attacker){
            string ret_str = "";

            return attacker.get_name() + " uses " + name;
        }
        


};

struct Attack : Move {
    protected:
        const int CRIT_CHANCE = 10;
        int damage;
        int accuracy;
        int dealt;
        int cost;
        bool targets = true;

    public:
        Attack(string name, int dmg, int accuracy = 100, int cst = 0) : Move{name, cst, dmg, accuracy, true}, damage{dmg}, accuracy{accuracy}, cost{cst}
        {}

        virtual string trigger(Creature& attacker, Creature& victim){
            string ret_str = "";
            if (rand() % CRIT_CHANCE == 0){
                dealt = damage * 2;
                ret_str += "CRIT! ";
            }
            else{
                dealt = damage + (rand() % (damage/3));
                dealt = (dealt*(100-victim.get_defense()))/100;
            }
        
            victim.modify_health(-dealt);
            return attacker.get_name() + " uses " + name + " on " + victim.get_name() + " dealing " + to_string(dealt) + " damage!";
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

struct Charge : Stat {
    
};


#endif