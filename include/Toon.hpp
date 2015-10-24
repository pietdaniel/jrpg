#ifndef TOON_HPP
#define TOON_HPP
#include "Global.hpp"
#include "ISpell.hpp"
#include <string>
#include <map>

class IHoldable;

class Toon   {
	public:
		Toon(std::string n, std::string d) {
			health = rand()%100+1;
			mana = 100;
			total_health = 100;
			total_mana = 100;
			name = n;
			description = d;
		}
		~Toon();
		int getHealth();

		std::string name;
		std::string description;
		int health;
		int total_health;
		int mana;
		int total_mana;
	private:
		std::string lore;
		// Equipable* helm;
		// Equipable* chest;
		// Equipable* legs;
		// Equipable* gloves;
		// Equipable* weapon;
		// Equipable* ring;
		std::map<std::string, ISpell*> spells;
};
#endif
