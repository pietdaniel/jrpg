#ifndef TEXTMENU_HPP
#define TEXTMENU_HPP
#include "TextMenuItem.hpp"
#include <vector>


class TextMenu {
	public: 
		TextMenu();
		TextMenu(TextMenuItem* cur, SDL_Rect* cont);
		TextMenu(std::string n, std::string d, std::vector<TextMenuItem> item_vector, SDL_Rect* box, bool selected );
		~TextMenu();
		TextMenuItem* getCurrent();
		std::vector<TextMenuItem> getCurrentOptions();
		TextMenuItem* getSelected();
		void setSelected(TextMenuItem* s);

		TextMenuItem* getPrevious();

		void incSelected();
		void decSelected();

		void setCurrent(TextMenuItem* c);
		// change container
		void resize(SDL_Rect box);
		SDL_Rect* getContainer();

		bool selected_huh;
	private:
		//the currently displayed text menu
		TextMenuItem* current;

		std::vector<TextMenuItem> currentOptions;
		//The option within the current TMI selected
		TextMenuItem* selected; 
		// the text container
		SDL_Rect container;
		int menuctr;
		
};
#endif



// TextMenu
	
// 	TextMenuItem current
// 	TextMenuItem selected
// 	int x
// 	int y
// 	SDL_Rect box

// 	create IMenu
// 		returns a vector of imenu items
// 		with x,y initliazied withi the imenu

// 	creates of list of the options
// 	in the current state

// 	gives them co-ordinates within the menu
// 	to draw

// 	~~
// 	should get keys held and deal with updating internally