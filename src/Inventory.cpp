#include "../include/Inventory.hpp"

Inventory::Inventory() {

}

Inventory::~Inventory() {
	
}

IHoldable* Inventory::get(std::string name) {
	return inventory[0];
}

IHoldable* Inventory::get(int at) {
	if (at<=inventory.size()) {
		return inventory[at];
	}
}

void Inventory::add(IHoldable* item) {
	inventory.push_back(item);
}

void Inventory::drop(IHoldable* item) {
	for(std::vector<IHoldable*>::const_iterator i = inventory.begin(); i != inventory.end(); ++i) {
		std::cout << item->name << " : item->name\n";
		std::cout << (*i)->name << " : *i->name\n";
	}
}
void Inventory::drop(std::string item) {
	std::vector<std::string> listed = list();
	int ctr=0;
	for(std::vector<std::string>::const_iterator i = listed.begin(); i != listed.end(); ++i) {
		if (item == (*i)) {
			inventory.erase(inventory.begin() + ctr);
		}
		ctr++;
	}
}

std::vector<std::string> Inventory::list() {
	std::vector<std::string> out;
	for (unsigned int i=0; i < inventory.size() ; i++) {
		out.push_back(inventory[i]->getName());
	}
	return out;
}

void Inventory::log() {
	std::cout<<"size: "<<inventory.size()<<"\n";
	for (unsigned int i=0; i < inventory.size() ; i++) {
		std::cout << inventory[i]->getName() << "\n";
	}
}