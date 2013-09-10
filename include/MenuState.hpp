#ifndef MenuState_HPP
#define MenuState_HPP
#include "IState.hpp"
#include "TextMenuItem.hpp"
#include "TextMenu.hpp"
#include "Global.hpp"
#include "Player.hpp"
#include <vector>
#include "boost/function.hpp"
#include "boost/bind.hpp"
#include "SpriteBase.hpp"
#include "NPC.hpp"
#include <boost/lexical_cast.hpp>

class MenuState : public IState {
	public:
		MenuState(Graphics* g);
		~MenuState();

		void init_inventory_pane();
		void init_character_pane();
		void update_character_pane();

		void init_select_pane();
		void update_select_pane();

		void init_not_party_menu();
		// i might be able to condense these
		void swapChar();
		void doSwap(Timer* timer);


		void tossItem();
		void useItem();


		void select_item();
		void select_char();
		void quit_menu();
		void debug();


		virtual void update(Timer* timer, bool* m_keysHeld);
		virtual void render();
		virtual bool getStatus();
		virtual std::string getNextState();
		virtual void setStatus(bool s);
		virtual void setPlayer(Player* p);
		virtual Player* getPlayer();
		Player* player;

	private:
		Graphics* graphics;
		bool status;
		std::string nextState;

		std::vector<NPC*> avatars;

		std::vector<TextMenuItem> SelectInvMenuItemV;
		std::vector<TextMenuItem> SelectPartyMenuItemV;
		TextMenu* SelectMenu;
		// item
		TextMenuItem* toss;
		TextMenuItem* equip;
		TextMenuItem* use;
		TextMenuItem* item_info;
		// character
		TextMenuItem* unequip;
		TextMenuItem* spell;
		TextMenuItem* swap;
		TextMenuItem* toon_info;

		TextMenuItem* quit;

		// lol didnt want to implement Avatar Class 
		// so just used NPC
		SDL_Surface* avatarBitmap;
		NPC* avatar1;
		NPC* avatar2;
		NPC* avatar3;

		std::vector<TextMenuItem> InventoryMenuItemV;
		TextMenu* InventoryMenu;

		std::vector<TextMenuItem> CharMenuItemV;
		TextMenu* CharMenu;

		TextMenu* NotPartyMenu;
		std::vector<TextMenuItem> NotPartyMenuV;
};
#endif