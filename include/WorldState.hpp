#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP
#include "IState.hpp"
#include "Global.hpp"
#include "SpriteBase.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "LuckyCoin.hpp"
#include "HealthPotion.hpp"
#include "Chest.hpp"
#include "WorldMap.hpp"
#include "Inventory.hpp"
#include "Toon.hpp"
#include "boost/function.hpp"
#include "boost/bind.hpp"
#include <vector>

class WorldState : public IState {
	public:
		WorldState(Graphics* g);
		~WorldState();

		void init_npcs();
		void init_player();
		void init_menu();
		void init_chests();
		void init_map();

		// this one needs which tiles are actually walls
		bool touches_wall(SDL_Rect box, std::vector<Tile*> tiles);
		bool touches_sprite(SDL_Rect box, std::vector<SpriteBase*> sprites);

		//presents the proper dialouge box
		std::string talk(SDL_Rect box, std::vector<SpriteBase*> npcs);

		virtual void update(Timer* timer, bool* m_keysHeld);
		virtual void render();
		virtual bool getStatus();
		virtual std::string getNextState();
		virtual void setStatus(bool s);

		virtual void setPlayer(Player* p);
		virtual Player* getPlayer();
		
		void quit_game();

		void open_menu();

		void movementHandler(Timer* timer, bool* m_keysHeld);
		void talk_handler();
		void chest_handler(bool* m_keysHeld);

		Player* player; // the player
	private:
		int direction; // this sucks fixme its for the players sprite


		// state machine stuff
		Graphics* graphics;
		bool status;
		std::string nextState;

		// menu items
		TextMenuItem* quit;
		TextMenuItem* lore;
		TextMenuItem* menu;
		TextMenuItem* WorldMenu;
		std::vector<TextMenuItem> WorldMenuV;
		TextMenu* Menu;

		// holds collection of tiles, level w/h, number of tiles in tile set (?) 
		WorldMap* map;
		//tileset of tileBitmap passed to graphics->drawTiles
		std::vector<SDL_Rect> tileset;


		// some toons for the players party
		Toon* alice;
		Toon* bob;
		Toon* zappa;
		Toon* greg;
		Toon* eve;
		
		SDL_Surface* tileBitmap; // grasswater
		SDL_Surface* charBitmap;
		SDL_Surface* npcBitmap;
		SDL_Surface* chestBitmap;
		SDL_Surface* townsfolk1Bitmap;
		SDL_Surface* townsfolk2Bitmap;
		SDL_Surface* doodadBitmap;

		// all deprecated atm
		std::vector<int> layer1;
		std::vector<int> layer2;
		std::vector<SDL_Rect> config;

		NPC* npc;
		NPC* townsfolk1;
		NPC* townsfolk2;
		NPC* townsfolk3;
		NPC* townsfolk4;
		NPC* townsfolk5;
		NPC* townsfolk6;
		NPC* townsfolk7;
		NPC* townsfolk8;
		std::vector<SpriteBase*> npcs;
		
		Chest* chest;
		IHoldable* coin;
		IHoldable* potion;

		std::vector<SpriteBase*> chests;

		// is talk window open
		bool is_talk;
		// can you even talk to someone
		bool talkable;
		std::string the_talk;

};
#endif