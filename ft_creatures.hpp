#include <stdlib.h>

struct Creature {
    protected:
        std::string name;
        int health;
        int energy;
        int speed;
        int defense;

        Creature(std::string name, int health_base = 0, int energy = 4, int speed = 5, int defense = 10)
            : name{name}, health{health_base}, energy{energy}, speed{speed}, defense{defense}
        {}


    
    public:
        int get_health(){
            return health;
        }

        int get_energy(){
            return energy;
        }

        int get_speed(){
            return speed;
        }

        int get_defense(){
            return defense;
        }
        std::string get_name(){
            return name;
        }

        friend std::ostream& operator<<(std::ostream& outs, const Creature& creature);
    
};

std::ostream& operator<<(std::ostream& outs, const Creature& creature) {
    return outs << creature.name << ", " << creature.health;
}


struct Player : Creature {
    public:
        Player(std::string name) : Creature{name}
        {
            this->name = "Player " + name;
            this->health = 100;
        }

    
};


struct Enemy : Creature {
    protected:
        Enemy(std::string name, int h_base = 0, int h_extra = 1) : Creature{name, h_base, h_extra}
        {
            this->health = health + (rand() % h_extra);
        }
};


struct GrooveGoblin : Enemy {
    protected:
        static const constexpr int health_base = 50;
        static const constexpr int health_extra = 20;
    public:
        GrooveGoblin(std::string name, int h_base = health_base, int h_extra = health_extra) : Enemy{name, h_base, h_extra}
        {
            this->name = "Groove Goblin " + name;
        }
};

struct DiscoDevil : Enemy {
    protected:
        static const constexpr int health_base = 80;
        static const constexpr int health_extra = 40;
    public:
        DiscoDevil(std::string name, int h_base = health_base, int h_extra = health_extra) : Enemy{name, h_base, h_extra}
        {
            this->name = "Disco Devil " + name;
        }
};