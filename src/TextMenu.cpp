#include "../include/TextMenu.hpp"


TextMenu::TextMenu() {
	menuctr=0;
}

TextMenu::TextMenu(TextMenuItem* cur, SDL_Rect* cont) {
	current = cur;
	currentOptions = current->getOptions();
	container = *cont;
	menuctr=0;
	selected_huh = false;
}

TextMenu::TextMenu(std::string n, std::string d, std::vector<TextMenuItem> item_vector, SDL_Rect* box, bool slctd ) {
	current = new TextMenuItem(n,d);
	current->setOptions(item_vector);
	currentOptions = current->getOptions();
	container = *box;
	menuctr = 0;
	selected_huh = slctd;
	if (selected_huh) {
		selected = &currentOptions.at(menuctr);
	}
}

TextMenu::~TextMenu() {

}

TextMenuItem* TextMenu::getCurrent() {
	return current;
}

std::vector<TextMenuItem> TextMenu::getCurrentOptions() {
	return current->getOptions();
}	
TextMenuItem* TextMenu::getSelected() {
	return selected;
}
void TextMenu::setSelected(TextMenuItem* s) {
	selected = s;
	selected_huh = true;
}
void TextMenu::setCurrent(TextMenuItem* c) {
	current = c;
}
// change container
void TextMenu::resize(SDL_Rect box) {
	container = box;
}
SDL_Rect* TextMenu::getContainer() {
	return &container;
}

void TextMenu::incSelected() {
	selected_huh = true;
	if (menuctr==0) {
		menuctr= currentOptions.size()-1;
	}else {
		menuctr = (menuctr-1) % currentOptions.size();
	}
	selected = &currentOptions.at(menuctr);
}

void TextMenu::decSelected() {
	selected_huh = true;
	menuctr = (menuctr+1) % currentOptions.size();
	selected = &currentOptions.at(menuctr);
}
