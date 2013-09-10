#include "../include/HealthPotion.hpp"


HealthPotion::~HealthPotion() {
	
}

void HealthPotion::action() {
	std::cout << "Health Potions needs a target";
}

void HealthPotion::action(Toon* target) {
	std::cout << target->getHealth() << "\n";
	// if (target.health < 90 ) {
	// 	target.health += 10;
	// }else {
	// 	target->health = 100;
	// }
}
