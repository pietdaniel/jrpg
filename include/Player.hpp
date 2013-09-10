#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "SpriteBase.hpp"
#include "Inventory.hpp"
#include "IHoldable.hpp"
#include "Global.hpp"
#include "Toon.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>

class Player : public SpriteBase  {
	public:
		Player() : SpriteBase() {
			setCharY(300);
			setCharX(300);
			setMapX(300);
			setMapY(300);

			keys[0]="DOWN0";
			keys[1]="UP0";
			keys[2]="RIGHT0";
			keys[3]="LEFT0";
			keys[4]="DOWN1";
			keys[5]="UP1";
			keys[6]="RIGHT1";
			keys[7]="LEFT1";
			keys[8]="DOWN2";
			keys[9]="UP2";
			keys[10]="RIGHT2";
			keys[11]="LEFT2";
			keys[12]="DOWN3";
			keys[13]="UP3";
			keys[14]="RIGHT3";
			keys[15]="LEFT3";
			setFrameKey("DOWN0");
			lastUpdate=0;
		}

		Player(int xpos, int ypos) : SpriteBase() {
			setCharY(ypos);
			setCharX(xpos);
			setMapX(xpos);
			setMapY(ypos);

			keys[0]="DOWN0";
			keys[1]="UP0";
			keys[2]="RIGHT0";
			keys[3]="LEFT0";
			keys[4]="DOWN1";
			keys[5]="UP1";
			keys[6]="RIGHT1";
			keys[7]="LEFT1";
			keys[8]="DOWN2";
			keys[9]="UP2";
			keys[10]="RIGHT2";
			keys[11]="LEFT2";
			keys[12]="DOWN3";
			keys[13]="UP3";
			keys[14]="RIGHT3";
			keys[15]="LEFT3";
			setFrameKey("DOWN0");
			lastUpdate=0;
		}

		~Player();

		// changes your direction by either updating the 
		// walkcycle or setting it to the new direction
		// fixme 100 could be a frame rate number
		virtual void updateSpriteFrame(std::string key, int ticks);

		// altering the walk frames by
		// changing the direction key
		virtual void cycleSpriteFrame();
		virtual void cycleSpriteFrame(int ticks);

		// associates a key string to an array of rectangles
		// used for cutting walk frames
		virtual void generateSpriteFrame(SDL_Surface* tileImage, int tileWidth, int tileHeight);

		// used for walk cycles
		virtual SDL_Rect getCurrentFrame();

		void addToParty(Toon* t);

		Inventory inventory;

		std::vector<Toon*> party;
		std::vector<Toon*> not_party;

		
	private:

		std::string keys[16];

		std::string frameKey;

		// character needs map position and screen position
		int charX;
		int charY;
		int mapX;
		int mapY;
		int velX;
		int velY;
		int health;
		int lastUpdate;
			// DOWN0, DOWN1, DOWN2, DOWN3, UP0 ..., LEFT0 ..., RIGHT0 ...,  
		std::map<std::string, SDL_Rect> frameCycle;
		SDL_Rect hitbox;


};
#endif