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
            return name + "  PWR: " + to_string(power) + "  ACC: " + to_string(accuracy) + "  CST: " + to_string(cost);
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
        bool targets;

    public:
        Stat(string name, int pwr, int acc = 100, int cst = 0, bool trgts = false) : 
            Move{name, cst, pwr, acc, trgts}, power{pwr}, accuracy{acc}, cost{cst}, targets{trgts}
        {}

        virtual string trigger(Creature& attacker){
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
                dealt = damage + ((attacker.get_strength() * damage)/100);
                dealt = (dealt*(100-victim.get_defense()))/100;
            }
        
            victim.modify_health(-dealt);
            ret_str += attacker.get_name() + " uses " + name + " on " + victim.get_name() + " dealing " + to_string(dealt) + " damage!";
            return ret_str;
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

struct PumpUp : Stat {
    protected:
        static constexpr int power = 2;
        static constexpr int acc = 100;
        static constexpr int cost = 0;
        static inline string name = "Pump it Up";
    
    public:
        PumpUp(string title = name, int pwr = power, int accuracy = acc, int cst = cost) : Stat{title, pwr, accuracy, cst}
        {}

        string trigger(Creature& attacker){
            attacker.modify_energy(power);
            return attacker.get_name() + " uses " + name + " and gains " + to_string(power + 1) + " energy!";
        }
};

struct TakeFive : Stat {
    protected:
        static constexpr int power = 40;
        static constexpr int acc = 100;
        static constexpr int cost = 0;
        static inline string name = "Take Five";
    
    public:
        TakeFive(string title = name, int pwr = power, int accuracy = acc, int cst = cost) : Stat{title, pwr, accuracy, cst}
        {}

        string trigger(Creature& attacker){
            int heal_amount = power + (rand() % (power/4));
            attacker.modify_health(heal_amount);
            return attacker.get_name() + " uses " + name + " and gains " + to_string(heal_amount) + " health!";
        }
};


#endif