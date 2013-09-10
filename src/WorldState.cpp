#include "../include/WorldState.hpp"

WorldState::WorldState(Graphics* g) {
	// Needed for every state subclass
	graphics = g;
	status = true;
	nextState = "battle";

	is_talk = false;
	talkable = false;
	the_talk = "nothing";

	init_player();

	init_npcs();

	init_chests();

	init_menu();
	
	init_map();
}

WorldState::~WorldState() {
	graphics->closeBitmap(tileBitmap);
	graphics->closeBitmap(charBitmap);
}

void WorldState::init_npcs() {
	// npc initializations
	npcBitmap = graphics->loadBitmap("build/npc1.bmp",0,255,255);
	npc = new NPC(200,200);
	npc->generateSpriteFrame(npcBitmap,50,50);
	npc->setFrameKey("11");
	npc->setSpeech("Yo man, it works");

	//						//
	// all the characters	//  god damn there are alot
	//						//
	townsfolk1Bitmap = graphics->loadBitmap("build/townsfolk.bmp",0,255,255);
	townsfolk1 = new NPC(500,500);
	townsfolk1->generateSpriteFrame(townsfolk1Bitmap,50,50);
	townsfolk1->setFrameKey("11");
	townsfolk1->setSpeech("Who do you love");

	townsfolk2 = new NPC(200,470);
	townsfolk2->generateSpriteFrame(townsfolk1Bitmap,50,50);
	townsfolk2->setFrameKey("40");
	townsfolk2->setSpeech("We all suffer from under consumption anxiety");

	townsfolk3 = new NPC(200,350);
	townsfolk3->generateSpriteFrame(townsfolk1Bitmap,50,50);
	townsfolk3->setFrameKey("30");
	townsfolk3->setSpeech("Welcome to the fantastical world, look out for snakes in the bushes");

	townsfolk4 = new NPC(400,200);
	townsfolk4->generateSpriteFrame(townsfolk1Bitmap,50,50);
	townsfolk4->setFrameKey("20");
	townsfolk4->setSpeech("Bugger off");

	townsfolk2Bitmap = graphics->loadBitmap("build/townsfolk2.bmp",0,255,255);
	townsfolk5 = new NPC(800,150);
	townsfolk5->generateSpriteFrame(townsfolk2Bitmap,50,50);
	townsfolk5->setFrameKey("11");
	townsfolk5->setSpeech("People like you makes everyone have to prepare something to say");

	townsfolk6 = new NPC(900,250);
	townsfolk6->generateSpriteFrame(townsfolk2Bitmap,50,50);
	townsfolk6->setFrameKey("40");
	townsfolk6->setSpeech("Have you seen my lover? Her name is lefty");

	townsfolk7 = new NPC(950,200);
	townsfolk7->generateSpriteFrame(townsfolk2Bitmap,50,50);
	townsfolk7->setFrameKey("30");
	townsfolk7->setSpeech("Maybe one day you'll battle eval");

	townsfolk8 = new NPC(800,500);
	townsfolk8->generateSpriteFrame(townsfolk2Bitmap,50,50);
	townsfolk8->setFrameKey("20");
	townsfolk8->setSpeech("Eval is the enemy");

	// creating npc vector
	npcs.push_back(npc);
	npcs.push_back(townsfolk1);
	npcs.push_back(townsfolk2);
	npcs.push_back(townsfolk3);
	npcs.push_back(townsfolk4);
	npcs.push_back(townsfolk5);
	npcs.push_back(townsfolk6);
	npcs.push_back(townsfolk7);
	npcs.push_back(townsfolk8);
}
void WorldState::init_player() {
	// player initializations
	charBitmap = graphics->loadBitmap("build/wizardchar.bmp",2,255,255);
	player = new Player();

	alice = new Toon("Alice", "Always on the recieving end"); // heal
	bob = new Toon("Bob", "Has a lot to say, not always sure if people are listening"); // tank
	zappa = new Toon("Zappa", "Powerful with magic"); // mage
	greg = new Toon("Greg", "He sucks");
	eve = new Toon("Eve", "Shes worth a spare rib");

	player->addToParty(alice);
	player->addToParty(bob);
	player->addToParty(zappa);
	player->addToParty(greg);
	player->addToParty(eve);


	// image, tile width, tile height
	player->generateSpriteFrame(charBitmap,50,50);
	// determines sprite draw direction, hacky solution for drawing char sprite
	direction = 0;
}
void WorldState::init_chests() {
	// chest
	coin = new LuckyCoin();
	potion = new HealthPotion();
	player->inventory.add(coin); // fixme REMOVE after testing
	chestBitmap = graphics->loadBitmap("build/box1.bmp",0,255,255);
	chest = new Chest(100,100, potion);
	chest->generateSpriteFrame(chestBitmap,50,50);
	chests.push_back(chest);
}
void WorldState::init_menu() {
	// open and close menu

	quit = new TextMenuItem("Quit","Exits the game", boost::bind(&WorldState::quit_game, this));
	lore = new TextMenuItem("Lore","Long ago they found the sleeping Omegagon, now they have all the power.");
	menu = new TextMenuItem("Menu","Mess with your party, check inventory, equip items, use spells", boost::bind(&WorldState::open_menu, this));

	SDL_Rect* box = new SDL_Rect();
	box->x = 300;
	box->y = 400;
	box->w = 300;
	box->h = 100;

	WorldMenuV.push_back(*quit);
	WorldMenuV.push_back(*menu);
	WorldMenuV.push_back(*lore);

	Menu = new TextMenu("Hub","Lets you save and open inventory/char panes", WorldMenuV, box, true);
	Menu->selected_huh = false;
	delete box;
	delete menu;
	delete lore;
	delete quit;

}
void WorldState::init_map(){
	// map initializations
	map = new WorldMap(1280, 960);
	// 			 char* file, int TOTAL_TILES, int TILE_SPRITES, int tileWidth, int tileHeight)
	map->loadMap("/home/barney/Documents/jrpg-alpha/build/first.map", 192, 12, 80, 80);
	tileBitmap = graphics->loadBitmap("build/grasswatertiles.bmp",0,255,255);
	doodadBitmap = graphics->loadBitmap("build/tileset.bmp",0,255,255);
	// helper to cut up the bmp
	tileset = graphics->createTileset(tileBitmap, 80, 80);
}

std::string WorldState::talk(SDL_Rect box, std::vector<SpriteBase*> npcs) {
	// iterator is just fancy here, 
	// the cream of the work is the dynamic cast
	std::vector<SpriteBase*>::iterator it;
	std::vector<SpriteBase*>::iterator end = npcs.end();
	for( it=npcs.begin(); it != end; ++it) {
		if( check_collision( box, (*it)->getHitbox() ) == true ) {
			return dynamic_cast<NPC*>(*it)->getSpeech();
		}
	}
    return "";
}

void WorldState::open_menu() {
	nextState = "menu";
	status = false;
}

void WorldState::quit_game() {
	graphics->endScene();
	
	delete npc;
	delete townsfolk1;
	delete townsfolk2;
	delete townsfolk3;
	delete townsfolk4;
	delete townsfolk5;
	delete townsfolk6;
	delete townsfolk7;
	delete townsfolk8;
	delete chest;
	delete coin;
	exit(0);
	SDL_Quit();
}

// the reason for this duplicate is because some tiles in the array are
// walls and some aren't
bool WorldState::touches_wall( SDL_Rect box, std::vector<Tile*> tiles) {
    for(unsigned int t = 0; t < tiles.size(); t++ ) {
    	// fixme 3 and 11 should be dynamic from tileset, tile[ t ]->is_wall()
        if( (( tiles[ t ]->getType() >= 3 ) && ( tiles[ t ]->getType() <= 11 )) ) {
            if( check_collision( box, tiles[ t ]->getBox() ) == true ) {
                return true;
            }
        }
    }
    return false;
}

bool WorldState::touches_sprite(SDL_Rect box, std::vector<SpriteBase*> sprites) {
	for(unsigned int t = 0; t < sprites.size(); t++ ) {
            if( check_collision( box, sprites[ t ]->getHitbox() ) == true ) {
                return true;
            }
    }
	return false;
}

void WorldState::movementHandler(Timer* timer, bool* m_keysHeld) {
	direction = 0;

	int delta = 2; // move distance

	// this is a keyboard handler for advanced movement control
	// it probably could be abstracted better
	if ( 
		(ARROW_KEY_STACK.back() == SDLK_UP) || 
		(ARROW_KEY_STACK.back() == SDLK_DOWN) || 
		(ARROW_KEY_STACK.back() == SDLK_LEFT) ||
		(ARROW_KEY_STACK.back() == SDLK_RIGHT)
		) {
			direction = ARROW_KEY_STACK.back();
	}else {
		if (ARROW_KEY_STACK.size() > 0) {
			ARROW_KEY_STACK.pop_back();
		}
	}

	if (direction!=0) {
		talkable = false;
	}

	// this handles collision, movement, and sprite update
	if (direction == SDLK_UP) {
		player->moveY(-1*delta);
		player->move(delta);
		if (touches_wall(player->getHitbox(),map->getTiles()) || touches_sprite(player->getHitbox(),npcs) || touches_sprite(player->getHitbox(), chests) ) {
			talk_handler();
			chest_handler(m_keysHeld);
			player->moveY(delta);
			player->move(delta);
		}
		player->updateSpriteFrame("UP",timer->get_ticks());

	}
	if (direction == SDLK_DOWN) {
    	player->moveY(delta);
    	player->move(delta);
    	if (touches_wall(player->getHitbox(),map->getTiles()) || touches_sprite(player->getHitbox(),npcs) || touches_sprite(player->getHitbox(), chests) ) {
    		talk_handler();
    		chest_handler(m_keysHeld);
			player->moveY(-1*delta);
			player->move(delta);
		}
    	player->updateSpriteFrame("DOWN",timer->get_ticks());
	}

	if (direction == SDLK_LEFT) {
		player->moveX(-1*delta);
		player->move(delta);
		if (touches_wall(player->getHitbox(),map->getTiles()) || touches_sprite(player->getHitbox(),npcs) || touches_sprite(player->getHitbox(), chests) ) {
			talk_handler();
			chest_handler(m_keysHeld);
			player->moveX(delta);
			player->move(delta);
		}
		player->updateSpriteFrame("LEFT",timer->get_ticks());
	}
	if (direction == SDLK_RIGHT) {    	
		player->moveX(delta);
		player->move(delta);
		if (touches_wall(player->getHitbox(),map->getTiles()) || touches_sprite(player->getHitbox(),npcs) || touches_sprite(player->getHitbox(), chests) ) {
			talk_handler();
			chest_handler(m_keysHeld);
			player->moveX(-1*delta);
			player->move(delta);
		}
	 	player->updateSpriteFrame("RIGHT",timer->get_ticks());
	}
}

void WorldState::talk_handler() {
	if ( touches_sprite(player->getHitbox(),npcs) ) {
		talkable = true;
		the_talk = talk(player->getHitbox(),npcs);
	}
}

void WorldState::chest_handler(bool* m_keysHeld) {
	if (touches_sprite(player->getHitbox(), chests) && m_keysHeld[ SDLK_a ]) {
		if (!chest->getOpen()) {
			chest->setOpen(true);
			player->inventory.add(chest->getContents());
			chest->setFrameKey("DOWN1");
		}
	}
}

void WorldState::update(Timer* timer, bool* m_keysHeld) {
	graphics->setCameraX(player->getX(),map->getLevelWidth());
	graphics->setCameraY(player->getY(),map->getLevelHeight());

	npc->updateSpriteFrame("1", timer->get_ticks());
	townsfolk1->updateSpriteFrame("1", timer->get_ticks());
	townsfolk2->updateSpriteFrame("4", timer->get_ticks());
	townsfolk3->updateSpriteFrame("3", timer->get_ticks());
	townsfolk4->updateSpriteFrame("2", timer->get_ticks());
	townsfolk5->updateSpriteFrame("1", timer->get_ticks());
	townsfolk6->updateSpriteFrame("4", timer->get_ticks());
	townsfolk7->updateSpriteFrame("3", timer->get_ticks());
	townsfolk8->updateSpriteFrame("2", timer->get_ticks());

	if (!Menu->selected_huh) {
		movementHandler(timer, m_keysHeld);
		if (m_keysHeld[ SDLK_a ] && is_talk) {
			is_talk = false;
			talkable = false;
			m_keysHeld[ SDLK_a ] = false;
		}

		if (m_keysHeld[ SDLK_a ] && talkable) {
			is_talk = true;
			m_keysHeld[ SDLK_a ] = false;
		}


	} else {
		if (m_keysHeld[ SDLK_RETURN ] ) {
			Menu->getSelected()->doCallback();
			m_keysHeld[ SDLK_RETURN ] = false;
		}
		// if (m_keysHeld[ SDLK_BACKSPACE ] ) {
		// 	Menu->setCurrent(WorldMenu);
		// 	m_keysHeld[ SDLK_BACKSPACE ] = false;
		// }
		if (m_keysHeld[ SDLK_DOWN ]) {
			Menu->decSelected();
			m_keysHeld[ SDLK_DOWN ] = false;
		}
		if (m_keysHeld[ SDLK_UP ]) {
			Menu->incSelected();
			m_keysHeld[ SDLK_UP ] = false;
		}
	}

	if (m_keysHeld[ SDLK_ESCAPE ]) {
		Menu->selected_huh = !Menu->selected_huh;
		m_keysHeld[ SDLK_ESCAPE ] = false;
	}
}

void WorldState::render() {
	graphics->beginScene();

	SDL_Rect cam = graphics->getCamera();

	// draw the background layer0
	graphics->drawTiles(tileBitmap, map->getTiles(), tileset);

	// just some dooodad fiddlings
	graphics->drawSprite(doodadBitmap,0,150,150-cam.x,200-cam.y,50,50);
	graphics->drawSprite(doodadBitmap,150,150,170-cam.x,220-cam.y,50,50);
	graphics->drawSprite(doodadBitmap,50,150,500-cam.x,220-cam.y,50,50);
	for (int i=0;i<200;i+=50) {
		graphics->drawSprite(doodadBitmap,100,150,150-cam.x+i,500-cam.y+i,50,50);
	}

	graphics->drawChar(chestBitmap,chest,&cam);
	graphics->drawChar(charBitmap,player,&cam);
	graphics->drawChar(npcBitmap,npc,&cam);
	graphics->drawChar(townsfolk1Bitmap,townsfolk1,&cam);
	graphics->drawChar(townsfolk1Bitmap,townsfolk2,&cam);
	graphics->drawChar(townsfolk1Bitmap,townsfolk3,&cam);
	graphics->drawChar(townsfolk1Bitmap,townsfolk4,&cam);
	graphics->drawChar(townsfolk2Bitmap,townsfolk5,&cam);
	graphics->drawChar(townsfolk2Bitmap,townsfolk6,&cam);
	graphics->drawChar(townsfolk2Bitmap,townsfolk7,&cam);
	graphics->drawChar(townsfolk2Bitmap,townsfolk8,&cam);


	// some titles
    graphics->drawText("World",18,100,20,255,255,255,0,0,0);

    // menu
    if (Menu->selected_huh) {
    	graphics->drawMenu(Menu);
    }
	
    if (is_talk) {
    	graphics->drawSpeech(the_talk, player->getX()-cam.x,player->getY()-cam.y);
    	//graphics->drawText(the_talk,18, player->getX()-100-cam.x,player->getY()-100-cam.y,255,255,255,0,0,0);
    }

    graphics->endScene();
}

bool WorldState::getStatus() {
	return status;
}

void WorldState::setStatus(bool s) {
	status = s;
}

std::string WorldState::getNextState() {
	return nextState;
}

Player* WorldState::getPlayer() {
	return player;
}

void WorldState::setPlayer(Player* p) {
	player = p;
}
