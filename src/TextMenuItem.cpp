#include "../include/TextMenuItem.hpp"

TextMenuItem::TextMenuItem(std::string t, std::string d) {
	title = t;
	description = d;
}

TextMenuItem::TextMenuItem(std::string t, std::string d, boost::function<void()> c) {
	title = t;
	description = d;
	callback = c;
}

TextMenuItem::~TextMenuItem() {

}

void TextMenuItem::setOptions(std::vector<TextMenuItem> o) {
	options = o;
}

void TextMenuItem::addOption(TextMenuItem item) {
	options.push_back(item);
}

void TextMenuItem::doCallback() {
	if (callback) {
		callback();
	}else {
		std::cout << "No such function to callback\n";
	}
}

std::vector<TextMenuItem> TextMenuItem::getOptions() {
	return options;
}

int TextMenuItem::getX() {
	return x;
}

int TextMenuItem::getY() {
	return y;
}

void TextMenuItem::setX(int i) {
	x = i;
}

void TextMenuItem::setY(int i) {
	y = i;
}

std::string TextMenuItem::getTitle() {
	return title;
}