#pragma once
#include <array>
#include <fstream>
using namespace std;

#define MACROSCOUNT 6
extern string errorMsg[1];
extern string macros[MACROSCOUNT];
using namespace std;

class Item {
public:
    string name;
    array<double, MACROSCOUNT> nutri;

    // Constructors/Destructor
    Item(string a, array<double, MACROSCOUNT> vals);
    Item(string line);
    ~Item();

    // Printing
    void print(fstream& out) const;
    void printOut();
};

