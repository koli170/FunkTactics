#ifndef FT_MOVES
#define FT_MOVES

#include <stdlib.h>
#include <string>

#include "ft_creatures.hpp"

using std::string;

struct Move {
    /* 
    Base class for all moves, contains:
    Variables
        string name, the name of the move
        int power, the power modifier of the move
        int accuracy, the percentage chance that the move will succeed
        int cost, the energy cost of the move
        bool targets, states whether the move requires targets

    Functions
        Basic constructor
        target(Creature& attacker, Creature& victim), base calculations for activating moves with targets
        target(Creature& attacker), base calculations for activating moves without targets
        string trigger(Creature& attacker, Creature& victim), triggers the effect of the move with targets
        string trigger(Creature& attacker), triggers the effect of the move without targets
        string get_stats(), returns a string containing the stats of the move
        string get_name(), returns a string containing the name of the move
        int get_cost(), returns the energy a move requires
        bool has_targets(), returns whether the move requires targets

    */
    protected:
        string name;
        int power;
        int cost;
        int accuracy;
        bool targets = false;

    public:
        Move(string name, int cost = 0, int pwr = 10, int acc = 100, bool trgts = false) : 
        name{name}, power{pwr}, cost{cost}, accuracy{acc}, targets{trgts}
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
    /*
    Base class for all moves that mainly effect creature stats:
    Variables
        int power, the power modifier of the move
        int accuracy, the percentage chance that the move will succeed
        int cost, the energy cost of the move
        bool targets, states whether the move requires targets

    Functions
        Basic constructor
        string trigger(Creature6 attacker), triggers the effect of the move without targets
        
    since no stat moves are targeted the class has no trigger for targets,
    very easily implemented if needed for future moves
    */

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
    /*
    Base class for all moves that mainly deal damage to creatures:
    Variables
        int crit_chance, the chance that the move will critical hit
        int power, the power modifier of the move
        int accuracy, the percentage chance that the move will succeed
        int dealt, the damage dealt by the move
        int cost, the energy cost of the move
        bool targets, states whether the move requires targets

    Functions
        Basic constructor
        string trigger(Creature& attacker, Creature& victim), triggers the effect of the move with targets

    since all attack moves are targeted the class has no trigger for no targets,
    very easily implemented if needed for future moves
    */
    protected:
        int crit_chance = 10;
        int power;
        int accuracy;
        int dealt;
        int cost;
        bool targets = true;

    public:
        Attack(string name, int pwr, int accuracy = 100, int cst = 0) : 
        Move{name, cst, pwr, accuracy, true}, power{pwr}, accuracy{accuracy}, cost{cst}
        {}

        virtual string trigger(Creature& attacker, Creature& victim){
            string ret_str = "";
            if (rand() % crit_chance == 0){
                dealt = power * 2;
                ret_str += "CRIT! ";
            }
            else{
                dealt = power + (rand() % (power/3));
                dealt = power + ((attacker.get_strength() * power)/100);
                dealt = (dealt*(100-victim.get_defense()))/100;
            }
        
            victim.modify_health(-dealt);
            ret_str += attacker.get_name() + " uses " + name + " on " + victim.get_name() + " dealing " + to_string(dealt) + " damage!";
            return ret_str;
        }
    

};

struct JazzHands : Attack {
    /* 
    A basic attack move that utilizes the base attack functions
    Does 20 damage
    Costs 0
    Hits 90% of the time
    */
    protected:
        static constexpr int damage = 20;
        static constexpr int acc = 90;
        static inline string name = "Jazz Hands";
    
    public:
        JazzHands(string title = name, int dmg = damage, int accuracy = acc) : Attack{title, dmg, accuracy}
        {}
};

struct Macarena : Attack {
    /* 
    A basic attack move that utilizes the base attack functions
    Does 45 damage
    Costs 2
    Hits 75% of the time
    */
    protected:
        static constexpr int damage = 45;
        static constexpr int acc = 75;
        static constexpr int cost = 2;
        static inline string name = "Macarena";
    
    public:
        Macarena(string title = name, int dmg = damage, int accuracy = acc, int cst = cost) : Attack{title, dmg, accuracy, cst}
        {}
};

struct PumpUp : Stat {
    /* 
    A move that gives the user 3 energy total
    Costs 0
    Hits 100% of the time
    */
    protected:
        static constexpr int power = 3;
        static constexpr int acc = 100;
        static constexpr int cost = 0;
        static inline string name = "Pump it Up";
    
    public:
        PumpUp(string title = name, int pwr = power, int accuracy = acc, int cst = cost) : Stat{title, pwr, accuracy, cst}
        {}

        string trigger(Creature& attacker){
            attacker.modify_energy(power-1);
            return attacker.get_name() + " uses " + name + " and gains " + to_string(power) + " energy!";
        }
};

struct TakeFive : Stat {
    /* 
    A move that heals the user 40+ health
    Costs 0
    Hits 100% of the time
    */
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

struct Tick : Stat {
    /* 
    A move that has a 50% chance to give energy
    Costs 0
    Hits 100% of the time
    */
    protected:
        static constexpr int power = 1;
        static constexpr int acc = 100;
        static constexpr int cost = 0;
        static inline string name = "Tick";
    
    public:
        Tick(string title = name, int pwr = power, int accuracy = acc, int cst = cost) : Stat{title, pwr, accuracy, cst}
        {}

        string trigger(Creature& attacker){
            if (rand() % 2 == 0){
                attacker.modify_energy(-1);
            }
            return attacker.get_name() + " uses " + name + " and their fuse sizzles!";
        }
};

struct MLBustdown : Attack {
    /* 
    A move that has a 50% chance to give energy
    Costs 0
    Hits 100% of the time
    */
    protected:
        static constexpr int power = 100;
        static constexpr int acc = 100;
        static constexpr int cost = 4;
        static inline string name = "Major League Bustdown";
    
    public:
        MLBustdown(string title = name, int pwr = power, int accuracy = acc, int cst = cost) : Attack{title, pwr, accuracy, cst}
        {}
};


#endif