#ifndef IHOLDABLE_HPP
#define IHOLDABLE_HPP
#include "Global.hpp"
#include "Toon.hpp"
#include <string>


// more like ItemBase...
class IHoldable {
	public:		
		std::string getName() {
			return name;
		}

		virtual void action() = 0;
		virtual void action(Toon* target) = 0;
		// more for various input types

		std::string name;
		std::string description;
		
	private:
	
};
#endif