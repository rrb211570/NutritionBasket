#include "pch.h"
#include "Item.h"
#include <iostream>

string errorMsg[1] = { "Incorrect format: " };
string macros[MACROSCOUNT] = { "Carbs", "Protein", "Sugar", "Fat", "Saturated", "Unsaturated" };

// Constructors/Destructor
Item::Item(string a, array<double, MACROSCOUNT> vals)
	: name(a), nutri(vals) {}
Item::Item(string line) {
	int start = 0;
	int commaIndex = line.find(',', start);
	name = line.substr(0, commaIndex);

	start = commaIndex;
	for (int i = 0; i < MACROSCOUNT - 1; ++i) {
		commaIndex = line.find(',', start + 1);
		nutri[i] = atof(line.substr(start + 1, commaIndex).c_str());
		start = commaIndex;
	}
	nutri[MACROSCOUNT - 1] = atof(line.substr(start + 1, line.length()).c_str());
}
Item::~Item() {}

// Printing
void Item::print(fstream& out) const {
	out << "Nutrition: " << name << endl << endl;
	for (int i = 0; i < MACROSCOUNT; ++i) {
		out << macros[i] << ": " << nutri[i] << endl;
	}
}
void Item::printOut() {
	cout << "Nutrition: " << name << endl << endl;
	for (int i = 0; i < MACROSCOUNT; ++i) {
		cout << macros[i] << ": " << nutri[i] << endl;
	}
}