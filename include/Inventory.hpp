#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#include <vector>
#include <string>

#include "IHoldable.hpp"

class Inventory  {
	public:
		Inventory();
		~Inventory();
		IHoldable* get(std::string name);
		IHoldable* get(int at);
		void add(IHoldable* item);
		void drop(IHoldable* item);
		void drop(std::string item);
		std::vector<std::string> list();
		void log();

	private:
		std::vector<IHoldable*> inventory;


};
#endif