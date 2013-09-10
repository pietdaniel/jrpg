#ifndef ISPELL_HPP
#define ISPELL_HPP
#include "ISpell.hpp" 
#include <string>

class ISpell {
	public:
		virtual void setName(std::string n) = 0;
		virtual std::string getName() = 0;
		virtual void setDescription(std::string d) = 0;
		virtual std::string getDescription() = 0;
	private:
		std::string name;
		std::string description;
};
#endif