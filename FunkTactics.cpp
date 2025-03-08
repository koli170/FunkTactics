#include <iostream>

#include "ft_creatures.hpp"
#include "ft_moves.hpp"

using namespace std;


int main() {
    std::srand(std::time({}));

    GrooveGoblin kyle = GrooveGoblin("Kyle");
    GrooveGoblin dave = GrooveGoblin("Dave");
    DiscoDevil cora = DiscoDevil("Coraxxus, Eater of All");
    DiscoDevil tar = DiscoDevil("Tarmacklemoore, Singer of Wonderwall");

    Player pl = Player("Kristján");

    JazzHands jh = JazzHands();

    cout << kyle << endl;
    cout << dave << endl;
    cout << cora << endl;
    cout << tar << endl;

    cout << endl;
    cout << "HERE COMES AN ATTACK!!" << endl;
    cout << kyle.target(cora) << endl;

    cout << cora << endl;

    return 0;
}