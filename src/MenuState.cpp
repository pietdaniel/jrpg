#include "../include/MenuState.hpp"

MenuState::MenuState(Graphics* g) {
	graphics = g;
	status = true;
	nextState = "world";
}

MenuState::~MenuState() {
}

void MenuState::init_inventory_pane() {
	InventoryMenuItemV.clear();

	// get the inventory
	std::vector<std::string> inv_list = player->inventory.list();
	// add to menu vector
    for (unsigned int i=0;i<inv_list.size();i++) {
    	// i think this is bad cause i cant delete the new text menu item FIXME
    	InventoryMenuItemV.push_back(*(new TextMenuItem(inv_list.at(i), "an item fixme",  boost::bind(&MenuState::select_item, this))));
    }
    //ad a quit function
    quit = new TextMenuItem("quit", "quit inventory",  boost::bind(&MenuState::quit_menu, this));
    InventoryMenuItemV.push_back(*quit);

	SDL_Rect* box = new SDL_Rect();
	box->x = 233;
	box->y = 350;
	box->w = 441;
	box->h = 325;

	InventoryMenu = new TextMenu("Inventory","What your currently holding",InventoryMenuItemV, box, true);
	delete box;
}

void MenuState::init_character_pane() {
	// clear container vector for updating
	CharMenuItemV.clear();
	avatars.clear();

	avatarBitmap = graphics->loadBitmap("build/avatar1.bmp",0,255,255);
	// these are inc'd by char_pane_x + padding + font_size
	avatar1 = new NPC();
	avatar1 = new NPC(50,125);
	avatar1->generateSpriteFrame(avatarBitmap,50,50);
	avatar1->setFrameKey("11");

	avatar2 = new NPC();
	avatar2 = new NPC(50,215);
	avatar2->generateSpriteFrame(avatarBitmap,50,50);
	avatar2->setFrameKey("21");

	avatar3 = new NPC();
	avatar3 = new NPC(50,305);
	avatar3->generateSpriteFrame(avatarBitmap,50,50);
	avatar3->setFrameKey("31");

	avatars.push_back(avatar1);
	avatars.push_back(avatar2);
	avatars.push_back(avatar3);

    for (unsigned int i=0;i<player->party.size();i++) {
    	CharMenuItemV.push_back(*(new TextMenuItem(player->party.at(i)->name, player->party.at(i)->description, boost::bind(&MenuState::select_char, this))));
    }

    SDL_Rect* box = new SDL_Rect();
	box->x = 25;
	box->y = 175;
	box->w = 175;
	box->h = 575;

	CharMenu = new TextMenu("Active Party","You know, the peeps you be chillin with right nah", CharMenuItemV, box, false);
	delete box;
}

void MenuState::update_character_pane() {
	CharMenuItemV.clear();

	 for (unsigned int i=0;i<player->party.size();i++) {
    	CharMenuItemV.push_back(*(new TextMenuItem(player->party.at(i)->name, player->party.at(i)->description, boost::bind(&MenuState::select_char, this))));
    }

    SDL_Rect* box = new SDL_Rect();
	box->x = 25;
	box->y = 175;
	box->w = 175;
	box->h = 575;

	CharMenu = new TextMenu("Active Party","You know, the peeps you be chillin with right nah", CharMenuItemV, box, false);
	delete box;
}

void MenuState::init_select_pane() {
	SelectInvMenuItemV.clear();
	SelectPartyMenuItemV.clear();

	toss 		= new TextMenuItem("toss","drop the current item",boost::bind(&MenuState::tossItem, this) );
	equip 		= new TextMenuItem("equip","equip the current item",boost::bind(&MenuState::select_char, this));
	use 		= new TextMenuItem("use","use the current item",boost::bind(&MenuState::useItem, this));
	item_info	= new TextMenuItem("info","get info on the item",boost::bind(&MenuState::select_char, this));
	SelectInvMenuItemV.push_back(*toss);
	SelectInvMenuItemV.push_back(*equip);
	SelectInvMenuItemV.push_back(*use);
	SelectInvMenuItemV.push_back(*item_info);

	unequip 	= new TextMenuItem("remove","unequip the current item",boost::bind(&MenuState::select_char, this));
	spell 		= new TextMenuItem("spell","use characters spell",boost::bind(&MenuState::select_char, this));
	swap 		= new TextMenuItem("swap","Switch a toon out",boost::bind(&MenuState::swapChar, this));
	toon_info	= new TextMenuItem("info","get info on the toon",boost::bind(&MenuState::select_char, this));
	SelectPartyMenuItemV.push_back(*unequip);
	SelectPartyMenuItemV.push_back(*spell);
	SelectPartyMenuItemV.push_back(*swap);
	SelectPartyMenuItemV.push_back(*toon_info);

 	SDL_Rect* box = new SDL_Rect();
	box->x = 225;
	box->y = 100;
	box->w = 450;
	box->h = 100;

	if (InventoryMenu->selected_huh) {
		SelectMenu = new TextMenu("Inventory", "the selection options for your inventory",SelectInvMenuItemV, box, false );
	} else {
		SelectMenu = new TextMenu("Party", "the selection options for your party",SelectPartyMenuItemV, box, false );
	}

	delete box;
	delete toss;
	delete equip;
	delete use;
	delete item_info;
	delete unequip;
	delete spell;
	delete swap;
	delete toon_info;
}

void MenuState::update_select_pane() {
	// check to see if we should switch
	if (InventoryMenu->selected_huh) {
		SelectMenu->getCurrent()->setOptions(SelectInvMenuItemV);
		// fixme i find this such bad praxis
		SelectMenu->getCurrent()->title = "Inventory";
		SelectMenu->getCurrent()->description = "the selection options for your inventory";
	} else if (CharMenu->selected_huh) {
		SelectMenu->getCurrent()->setOptions(SelectPartyMenuItemV);
		SelectMenu->getCurrent()->title = "Party";
		SelectMenu->getCurrent()->description = "the selection options for your party";
	}
}

void MenuState::tossItem() {
	// remove from menu
	// remove from inventory
	player->inventory.drop(InventoryMenu->getSelected()->title);
	init_inventory_pane();
	SelectMenu->selected_huh = false;
}

void MenuState::useItem() {
	std::cout << player->party.at(0)->name << "\n";
	std::cout << player->inventory.get(0)->name << "\n";

	player->inventory.get(0)->action(player->party.at(0));
}

void MenuState::init_not_party_menu() {
	NotPartyMenuV.clear();
	for(std::vector<Toon*>::const_iterator it = player->not_party.begin(); it != player->not_party.end(); ++it) {
		NotPartyMenuV.push_back(*(new TextMenuItem((*it)->name,(*it)->description)));
	}
	SDL_Rect* box = new SDL_Rect();
	box->x = 225;
	box->y = 225;
	box->w = 450;
	box->h = 100;
	NotPartyMenu = new TextMenu("Inactive Party", "People you can swap in", NotPartyMenuV, box, true);
	NotPartyMenu->selected_huh = false;
	delete box;
}

void MenuState::swapChar() {
	// populate swap menu
	init_not_party_menu();
	// select proper menu
	NotPartyMenu->selected_huh = true;
	SelectMenu->selected_huh = false;
}

void MenuState::doSwap(Timer* timer) {
	int np=0;
	int p=0;
	// find the right toon in the inactive party
	for(std::vector<Toon*>::const_iterator it = player->not_party.begin(); it != player->not_party.end(); ++it) {
		// if we have the right one
		if ((*it)->name == NotPartyMenu->getSelected()->title) {
			// find the right active toon
			for(std::vector<Toon*>::const_iterator qt = player->party.begin(); qt != player->party.end(); ++qt) {
				// if we have the right one
				if ((*qt)->name == CharMenu->getSelected()->title) {
					// do the swaps
					player->party.insert(player->party.begin()+p+1,(*it));
					player->not_party.insert(player->not_party.begin() + np + 1,(*qt));
					player->party.erase(player->party.begin() + p);
					player->not_party.erase(player->not_party.begin() + np);

					avatars[p]->updateSpriteFrame(boost::lexical_cast<std::string>(p+2), timer->get_ticks());

					goto stop;
				}
				++p;
			}
		}
		++np;
	}
	// using gotos fuck yeah
	stop: 
	NotPartyMenu->selected_huh = false;
	InventoryMenu->selected_huh = true;
	update_character_pane();
	update_select_pane();
}

void MenuState::select_item() {
	SDL_Rect* box = new SDL_Rect();
	box->x = 225;
	box->y = 100;
	box->w = 450;
	box->h = 100;
	SelectMenu = new TextMenu("Inventory", "the selection options for your inventory",SelectInvMenuItemV, box, true );
	delete box;

	InventoryMenu->selected_huh = false;
}

void MenuState::select_char() {
	SDL_Rect* box = new SDL_Rect();
	box->x = 225;
	box->y = 100;
	box->w = 450;
	box->h = 100;
	SelectMenu = new TextMenu("Party", "the selection options for your party",SelectPartyMenuItemV, box, true );
	delete box;

	CharMenu->selected_huh = false;
}

void MenuState::quit_menu() {
	status=false;
}

void MenuState::update(Timer* timer, bool* m_keysHeld) {

	avatars[0]->cycleSpriteFrame(timer->get_ticks());
	avatars[1]->cycleSpriteFrame(timer->get_ticks());
	avatars[2]->cycleSpriteFrame(timer->get_ticks());

	// these three conditionals are so similiar, i want to abstract this
	
	// if we are in the inventory pane do the key handling
	if (InventoryMenu->selected_huh) {
		if (m_keysHeld[ SDLK_RETURN ] ) {
			InventoryMenu->getSelected()->doCallback();
			m_keysHeld[ SDLK_RETURN ] = false;
		}
		if (m_keysHeld[ SDLK_DOWN ]) {
			InventoryMenu->decSelected();
			m_keysHeld[ SDLK_DOWN ] = false;
		}
		if (m_keysHeld[ SDLK_UP ]) {
			InventoryMenu->incSelected();
			m_keysHeld[ SDLK_UP ] = false;
		}


		if (m_keysHeld[ SDLK_LEFT ]) {
			CharMenu->incSelected();
			InventoryMenu->selected_huh = false;
			m_keysHeld[ SDLK_LEFT ] = false;
			update_select_pane();
		}
		if (m_keysHeld[ SDLK_RIGHT ]) {
			CharMenu->incSelected();
			InventoryMenu->selected_huh = false;
			m_keysHeld[ SDLK_RIGHT ] = false;
			update_select_pane();
		}

		if (m_keysHeld[ SDLK_ESCAPE ]) {
		 	status = false;		
		 	m_keysHeld[ SDLK_ESCAPE ] = false;
		}
	}

	// if we are in the char pane do the key handling
	if (CharMenu->selected_huh) {
		if (m_keysHeld[ SDLK_RETURN ] ) {
			CharMenu->getSelected()->doCallback();
			m_keysHeld[ SDLK_RETURN ] = false;
		}
		if (m_keysHeld[ SDLK_DOWN ]) {
			CharMenu->decSelected();
			m_keysHeld[ SDLK_DOWN ] = false;
		}
		if (m_keysHeld[ SDLK_UP ]) {
			CharMenu->incSelected();
			m_keysHeld[ SDLK_UP ] = false;
		}


		if (m_keysHeld[ SDLK_LEFT ]) {
			InventoryMenu->incSelected();
			CharMenu->selected_huh = false;
			m_keysHeld[ SDLK_LEFT ] = false;
			update_select_pane();
		}
		if (m_keysHeld[ SDLK_RIGHT ]) {
			InventoryMenu->incSelected(); // fix
			CharMenu->selected_huh = false;
			m_keysHeld[ SDLK_RIGHT ] = false;
			update_select_pane();
		}

		if (m_keysHeld[ SDLK_ESCAPE ]) {
		 	status = false;		
		 	m_keysHeld[ SDLK_ESCAPE ] = false;
		}
	}

	// if we are in the select pane do the key handling
	if (SelectMenu->selected_huh) {
		if (m_keysHeld[ SDLK_RETURN ] ) {
			SelectMenu->getSelected()->doCallback();
			m_keysHeld[ SDLK_RETURN ] = false;
		}
		if (m_keysHeld[ SDLK_DOWN ]) {
			SelectMenu->decSelected();
			m_keysHeld[ SDLK_DOWN ] = false;
		}
		if (m_keysHeld[ SDLK_UP ]) {
			SelectMenu->incSelected();
			m_keysHeld[ SDLK_UP ] = false;
		}


		if (m_keysHeld[ SDLK_ESCAPE ]) {
			SelectMenu->selected_huh = false;
			if (SelectMenu->getCurrent()->getTitle() == "Inventory") {
				InventoryMenu->incSelected();
			}else {
				CharMenu->incSelected(); // fixme here and above
			}
			m_keysHeld[ SDLK_ESCAPE ] = false;
		}
	}


	// if the character swap is activated
	if (NotPartyMenu->selected_huh) {
		if (m_keysHeld[ SDLK_RETURN ] ) {
			doSwap(timer);
			m_keysHeld[ SDLK_RETURN ] = false;
		}
		if (m_keysHeld[ SDLK_DOWN ]) {
			NotPartyMenu->decSelected();
			m_keysHeld[ SDLK_DOWN ] = false;
		}
		if (m_keysHeld[ SDLK_UP ]) {
			NotPartyMenu->incSelected();
			m_keysHeld[ SDLK_UP ] = false;
		}

		if (m_keysHeld[ SDLK_ESCAPE ]) {
			NotPartyMenu->selected_huh = false;
			SelectMenu->incSelected(); // fixme here and above, using this to change selected_huh and selected item
			m_keysHeld[ SDLK_ESCAPE ] = false;
		}
	}
}

void MenuState::render() {
	graphics->beginScene();
    graphics->drawText("Char Menu",18,25,25,255,255,255,0,0,0);

	graphics->drawCharPane(CharMenu, avatars, player->party, avatarBitmap);

	graphics->drawMenu(InventoryMenu);
	graphics->drawMenu(SelectMenu);

	// for swapping party
	if (NotPartyMenu->selected_huh) {
		graphics->drawMenu(NotPartyMenu);
	}

    graphics->endScene();
}

bool MenuState::getStatus() {
	return status;
}

void MenuState::setStatus(bool s) {
	status = s;
}

std::string MenuState::getNextState() {
	return nextState;
}

Player* MenuState::getPlayer() {
	return player;
}

void MenuState::setPlayer(Player* p) {
	player = p;
	init_inventory_pane();
	init_character_pane();
	init_select_pane();
	init_not_party_menu();
}

void MenuState::debug() {
	std::cout << "\n";
	std::cout << InventoryMenu->selected_huh 	<< " : inv selected_huh\n";
	std::cout << CharMenu->selected_huh 		<< " : char selected_huh\n";
	std::cout << SelectMenu->selected_huh 		<< " : select selected_huh\n";
	std::cout << (SelectMenu->getCurrent()->getTitle() == "Inventory") << " : inventory == gettitle\n";
	std::cout << (SelectMenu->getCurrent()->getTitle() == "Party") << " : Party == gettitle\n";
}