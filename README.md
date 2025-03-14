# Funk Tactics - PA4

This is a simple music themed JRPG that runs in the terminal. It features randomized combat, a clean UI, multiple enemies and moves, an energy meter, sprites and more!

It was made for a programming assignment in the class T-403-FORC in RU. Below you will find a quick instillatin guide and descriptions for both users and programmers!

---

## Installation

**Requirements**:  
- C++ compiler (compatable with C++20)
- If UI loads incorrectly, you might need to change your terminal settings to allow custom colors etc.


**Steps**:  
```bash
git clone https://github.com/koli170/FunkTactics.git
cd FunkTactics
make
```
## User Guide

In Funk Tactics you take control of the player character and need to get your groove on to overcome three battles against 1 - 3 enemies of varying types *(see below)*. You have multiple moves at your disposal *(see below)*, that you must use strategically to OUT FUNK the competition.

Combat features 2 phases, player turn and enemy turn

First the player selects a move, then if the move is targeted the user selects a target. Some moves cost energy and thus cannot be used if the user does not have enough energy. The user gains energy whenever he uses a zero cost move. If a move misses energy is not consumed.

After the players turn the enemies attack from left to right, they follow the same rules regarding energy as the player and their choices are random. The exact health and energy of an enemy is hidden, enemies have varying amount of health and always have a maximum of four energy.

If all enemies are defeated, the player is victorious and gets to move on.\
If the player is defeated, then the enemies are victorious.

### Move list
The moves featured in this game are the following:

- Jazz Hands - POW: 20   ACC: 90   COST: 0\
The basic attack move, hits one enemy

- Macarena - POW: 45   ACC: 75   COST: 2\
A stronger attack, hits one enemy

- Pump it up - POW: 3   ACC: 100   COST: 0\
Charges up 3 energy

- Take five - POW: 40   ACC: 100   COST: 0\
Heals the user

### Enemy list
The enemies featured in this game are the following:

- Groove Goblin - BASE HP: 50   DEF: 5   STR : 5\
The basic grunt enemy, weak on its own but can be scary in packs. They have access to the moves Jazz Hands and Macarena.

- Disco Devil - BASE HP: 90   DEF: 20   STR: 15\
A stronger, more formiddable foe. Stronger in every way with even more moves to groove with. They aren't the smartest though. They have access to the moves Jazz Hands, Macarena, Pump it up, and Take five.


## Programmer Guide
The program consists of 6 files, below you will find information on all of them.

- FunkTactics.cpp\
This is the base file that is built and runs the game, it consists of very little code, any programmer should be able to read and understand in with relative ease.

- ft_creatures.hpp\
This file contains the structures for the creatures, it has a base structure named Creature which contains the base variables needed for creatures along with functions to get variables, modify health and energy, and use a move.\
It has the player class which is a child of the Creature struct. It contains some base stat variables and a known_moves vector. It contains a constructor and within that constructor you will find the moves the player starts with, if you wish to add more moves to the player you can simply push them to the known_moves vector. It also has functions to list player moves and use moves. When a player is constructed an extra adjective is added to the front of the name using the function funkify!\
The file also contains the Enemy struct which is also a child of the Creature struct. It has a known_moves vector and a function for selecting a random move and using it on a given creature. When an enemy is constructed, a variable called extra health is also used to give them a varying amount of bonus health on top of their base health.\
The enemy types themselves are Structures that are childs of the Enemy struct and contain variables for their base stats, moves, and sprite. Its constructor contains the moves they know simialrly to the player struct. Below the Enemy types you will see a vector of names and the sprite varible. When an enemy is created it chooses a name at random from the vector.

- ft_moves.hpp\
This file contains the structures for the moves, it has a base structure named Move which contains the base variables needed for the moves along with functions to get variables, target creatures, and trigger effects. When a creature is targeted, the move checks if it hits and if it does it triggers its effect using trigger. Some moves cost energy to use, those who cost zero give one energy to the user when used. The targets boolean is used to know whether a move requires targets.\
The next structure is Stat, its a child of Move and has basic stat variables and a trigger function which on its only returns a string. Stat is the parent struct for moves that are designed to modify stats.\
The next structure is Attack, its a child of Move and has basic stat variables along with crit chance and dealt. Crit chance is the chance that an attack will be a critical hit and dealt is the total damage dealt to the victim creature. The struct has a trigger function which deals damage to a victim creature and returns a string message of what happened.\
Below that you will find the structs for the moves themselves. Each move is either a child of Attack or Stat depending on what the move does, attacking moves can make use of the base trigger function from Attack for their trigger effect, Stat moves have no base trigger effect so they must have their own trigger function. Attack moves can also have their own trigger functions.


- ft_fight.hpp

- ft_drawer.hpp

- ft_sprites.hpp



## Known Bugs

ICELANDIC LETTERS, TWO ENTERS



TODO: OTHER MOVES, ONGOING

TODO: ICELANDIC LETTES SCREW WITH UI

TODO: SCALARS

TODO: ON FIGHT ENTER, TWO ENTERS REQUIRED

TODO: RANDOM UNIOFORM INT DISTRIBUTION

TODO: NEFNA SYSTEM  CLEAR THING

GOOD COMMIT VERSION: # 88112bc