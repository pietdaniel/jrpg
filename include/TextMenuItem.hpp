#ifndef TEXTMENUITEM_HPP
#define TEXTMENUITEM_HPP
#include "Global.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include "boost/function.hpp"
#include "boost/bind.hpp"


class TextMenuItem {
	public:
		TextMenuItem(std::string t, std::string d);
		TextMenuItem(std::string t, std::string d, boost::function<void()> c);
		~TextMenuItem();
		void setOptions(std::vector<TextMenuItem> o);
		void addOption(TextMenuItem item);
		std::vector<TextMenuItem> getOptions();
		int getX();
		int getY();
		void setX(int i);
		void setY(int i);

		std::string getTitle();
		void doCallback();

		std::string title;
		std::string description;
		
	private:
		boost::function<void()> callback;
		int x;	// position within TextMenu rect
		int y;	//
		std::vector<TextMenuItem> options;
};
#endif

