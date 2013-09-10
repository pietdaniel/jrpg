#ifndef HEALTHPOTION_HPP
#define HEALTHPOTION_HPP
#include "IHoldable.hpp"
#include "Global.hpp"
#include <string>


class HealthPotion : public IHoldable  {
	public:
		HealthPotion() : IHoldable() {
			name = "Health Potion";
			description = "Heals 10 HP";
		}

		~HealthPotion();

		virtual void action();
		virtual void action(Toon* target);

};
#endif