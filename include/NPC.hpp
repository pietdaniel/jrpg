#ifndef NPC_HPP
#define NPC_HPP
#include "SpriteBase.hpp"
#include "Global.hpp"
#include <vector>
#include <map>
#include <string>

class NPC : public SpriteBase  {
	public:
		NPC() : SpriteBase() {

			// Now they are ROW,COL

			keys[0] ="10";
			keys[1] ="20";
			keys[2] ="30";
			keys[3] ="40";
			keys[4] ="11";
			keys[5] ="21";
			keys[6] ="31";
			keys[7] ="41";
			keys[8] ="12";
			keys[9] ="22";
			keys[10]="32";
			keys[11]="42";
			keys[12]="13";
			keys[13]="23";
			keys[14]="33";
			keys[15]="43";
			setFrameKey("10");
			lastUpdate=0;
		}

		NPC(int xpos, int ypos) : SpriteBase() {
			setCharX(xpos);
			setCharY(ypos);
			setMapX(xpos);
			setMapY(ypos);

			keys[0] ="10";
			keys[1] ="20";
			keys[2] ="30";
			keys[3] ="40";
			keys[4] ="11";
			keys[5] ="21";
			keys[6] ="31";
			keys[7] ="41";
			keys[8] ="12";
			keys[9] ="22";
			keys[10]="32";
			keys[11]="42";
			keys[12]="13";
			keys[13]="23";
			keys[14]="33";
			keys[15]="43";
			setFrameKey("10");
			lastUpdate=0;
		}

		// NPC(int xpos, int ypos);
		// NPC(SDL_Surface* tileImage, int width, int height);
		~NPC();

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

		virtual SDL_Rect getCurrentFrame();

		std::string getSpeech();
		void setSpeech(std::string text);

		
	private:

		std::string speech;

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