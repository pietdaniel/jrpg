#ifndef EQUIPABLE_HPP
#define EQUIPABLE_HPP
#include "IHoldable.hpp"
#include "Global.hpp"
#include <string>

class Equipable : public IHoldable {
	public:
		Equipable() : IHoldable() {
			name = "";
			description = "";
		}

		~Equipable();

		virtual void action();
		virtual void action(Toon* target);

};
#endif