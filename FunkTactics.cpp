#include <iostream>

#include "ft_creatures.hpp"

using namespace std;


int main() {
    std::srand(std::time({}));

    GrooveGoblin test = GrooveGoblin("Kyle");
    GrooveGoblin test1 = GrooveGoblin("Dave");
    DiscoDevil test3 = DiscoDevil("Coraxxus, Eater of All");
    DiscoDevil test4 = DiscoDevil("Tarmacklemoore, Singer of Wonderwall");

    cout << test << endl;
    cout << test1 << endl;
    cout << test3 << endl;
    cout << test4 << endl;

    return 0;
}