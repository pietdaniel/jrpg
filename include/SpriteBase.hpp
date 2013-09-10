#ifndef SPRITEBASE_HPP
#define SPRITEBASE_HPP
#include "SpriteBase.hpp"
#include "Global.hpp"
#include <vector>
#include <map>
#include <string>

// more like CharacterBase... more like SpriteBase
class SpriteBase {
	public:
		
		SpriteBase() {
			velX = 0;
			velY = 0;
			hitbox.w = 50; // fixme
			hitbox.h = 50;		
		}


		void setCharX(int x) {
			charX = x;
			hitbox.x = charX;
		}
		void setCharY(int y) {
			charY = y;
			hitbox.y = charY;
		}

		void moveX(int delta) {
			velX+=delta;
		}

		void moveY(int delta) {
			velY+=delta;
		}

		void move(int delta) {
		    charX += velX;
		    if( ( charX < 0 ) || ( charX + 25 > 1280 ) ) { // fix me make level_width dynamic
		        charX -= velX;
		    }
			hitbox.x=charX;

		    charY += velY;
		    if( ( charY < 0 ) || ( charY + 25 > 960 ) ) { //fix me make level_height dynamic
		        charY -= velY;
		    }
		    hitbox.y=charY;

		    if (velX>0) {
		    	velX-=delta;
		    }
		    if (velX<0) {
		    	velX+=delta;
		    }
		    if (velY>0) {
		    	velY-=delta;
		    }
		    if (velY<0) {
		    	velY+=delta;
		    }
		    
		}

		void setFrameKey(std::string key) {
			framekey = key;
		}

		std::string getFrameKey() {
			return framekey;
		}

		SDL_Rect getHitbox() {
			return hitbox;
		}

		int getX() {
			return charX;
		}

		int getY() {
			return charY;
		}

		std::string getKey(int x) {
			return keys[x];
		}

		void setMapX(int x) {
			mapX = x;
		}
		void setMapY(int y) {
			mapY = y;
		}
		void moveMapX(int x) {
			mapX += x;
		}
		void moveMapY(int y) {
			mapY += y;
		}
		int getMapX() {
			return mapX;
		}
		int getMapY() {
			return mapY;
		}

		virtual void updateSpriteFrame(std::string key, int ticks) = 0;

		// cycleSpriteFrame
		virtual void cycleSpriteFrame() = 0;
		virtual void cycleSpriteFrame(int ticks) = 0;

		// sets the sprite frames associated with the string keys
		virtual void generateSpriteFrame(SDL_Surface* tileImage, int tileWidth, int tileHeight) = 0;

		virtual SDL_Rect getCurrentFrame() = 0;

	private:
		std::string keys[16];
		
		// frame_key
		std::string framekey; 
		// character needs map position and screen position
		// not char x but screenX
		int charX;
		int charY;
		int mapX;
		int mapY;
		int velX;
		int velY;
		// int health;
		// int lastUpdate;
			// DOWN0, DOWN1, DOWN2, DOWN3, UP0 ..., LEFT0 ..., RIGHT0 ..., 

		//frames
		std::map<std::string, SDL_Rect> frameCycle;
		
		SDL_Rect hitbox;
};
#endif