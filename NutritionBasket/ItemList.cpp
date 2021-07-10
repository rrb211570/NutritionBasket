#include "pch.h"
#include "ItemList.h"
#include <iostream>

// Persistent Memory I/O
void ItemList::load(fstream& in) {
	char str[256];
	while (in.getline(str, 256)) {
		try {
			string line(str);
			Item item = Item(line);
			this->put(item.name, item.nutri);
		}
		catch (const string msg) {
			cerr << msg << endl;
			break;
		}
	}
}
void ItemList::save(fstream& out) {
	for (auto item : items) {
		out << item.second.name << ",";
		for (int i = 0; i < MACROSCOUNT - 1; ++i) out << item.second.nutri[i] << ",";
		out << item.second.nutri[MACROSCOUNT - 1];
		out << endl;
	}
}

// Modifications
void ItemList::put(string a, array<double, MACROSCOUNT> vals) {
	if (items.find(a) != items.end()) this->remove(a);
	items.insert({ a, Item(a, vals) });
	for (int i = 0; i < MACROSCOUNT; ++i) sumNutri[i] += vals[i];
}
void ItemList::remove(string name) {
	if (items.find(name) != items.end()) {
		Item item = items.at(name);
		for (int i = 0; i < MACROSCOUNT; ++i) sumNutri[i] -= item.nutri[i];
		items.erase(name);
	}
	else cout << "Err: Item \"" << name << "\" DNE";
}
void ItemList::clear() {
	items.clear();
	memset(&sumNutri, 0, sizeof(sumNutri));
}

// Features
array<double, MACROSCOUNT> ItemList::average(int days) {
	array<double, MACROSCOUNT> vals = sumNutri;
	for (int i = 0; i < MACROSCOUNT; ++i) vals[i] /= days;
	return vals;
}

// Printing
void ItemList::print(fstream& out) {
	for (std::pair<std::string, Item> elem : items) {
		elem.second.print(out);
	}
}
void ItemList::printSum() {
	for (int i = 0; i < MACROSCOUNT; ++i) cout << sumNutri[i] << " ";
}
void ItemList::printOut() {
	for (std::pair<std::string, Item> elem : items) {
		elem.second.printOut();
	}
}
