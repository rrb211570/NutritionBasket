#pragma once
#include "Item.h"
#include <map>

class ItemList {
    map<string, Item> items;
    array<double, MACROSCOUNT> sumNutri = { 0,0,0,0,0,0 };
public:
    // Constructor
    ItemList() {}

    // Persistent Memory I/O
    void load(fstream& in);
    void save(fstream& out);

    // Modifications
    void put(string a, array<double, MACROSCOUNT> vals);
    void remove(string name);
    void clear();

    // Features
    array<double, MACROSCOUNT> average(int days);

    // Printing
    void print(fstream& out);
    void printSum();
    void printOut();
};

