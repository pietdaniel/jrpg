//Graphics.hpp
#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include "Global.hpp"
#include "Tile.hpp"
#include "TextMenu.hpp"
#include "SpriteBase.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "Inventory.hpp"
#include "Toon.hpp"
#include <sstream>

class Graphics {
	public:
		Graphics(int winWidth, int winHeight, const char* winTitle);
		~Graphics();

		void drawBox(SDL_Rect* box, int color);
		void drawMenu(TextMenu* menu);
		void drawMenu(TextMenu* menu, int padding);
		void drawChar(SDL_Surface* charBitmap, SpriteBase* player,SDL_Rect* cam);
		void drawChar(SDL_Surface* charBitmap, SpriteBase* player);

		// againlol NPC is just used cause im to lazy to make Avatar.o which would just be a redux on NPC
		// spritebase you say? well should update and cycle frame be object specific?
		void drawCharPane(TextMenu* CharMenu, std::vector<NPC*> avatars, std::vector<Toon*> party, SDL_Surface* avatarBitmbap);

		void drawInventory(Inventory &inventory);

		// write a helper to convert hex numbers to SDL_Color

		// loadBitmap and closeBitmap must be coupled
		SDL_Surface* loadBitmap(const char* bitmapFileName, int transR, int transG, int transB);
		void closeBitmap(SDL_Surface* bitamp);

		// bookend drawing routines
		void beginScene();
		void endScene();

		void drawSprite(SDL_Surface* imageSurface,
						int srcX, int srcY,
						int dstX, int dstY,
						int wdth, int hght);

		SDL_Surface* scaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height);
		Uint32 ReadPixel(SDL_Surface *surface, int x, int y);
		void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);


		// deprecated fixme, used in render
		void drawText(const char* string, int size,
					  int x, int y,
					  int frR, int frG, int frB,
					  int bR, int bG, int bB);

		void drawText(std::string string, int size,
				  int x, int y,
				  int frR, int frG, int frB,
			  	  int bR, int bG, int bB);

		void setBgColor(int r, int g, int b);

		// used to draw text boxes
		void drawSpeech(std::string speech, int x, int y);

		std::vector<std::string> makeLines(std::vector<std::string> words);

		// returns a  vector of words within the string
		std::vector<std::string> getWords(std::string text);

		// deprecated use draw tiles
		void drawTilemap(SDL_Surface* tileImage, std::vector<SDL_Rect> config, std::vector<int> tilemap);

		std::vector<SDL_Rect> createTileset(SDL_Surface* tileImage, int tileWidth, int tileHeight);

		void setCameraX(int charX, int LEVEL_WIDTH);
		void setCameraY(int charY, int LEVEL_HEIGHT);

		SDL_Rect getCamera();

		void drawTiles(SDL_Surface* tileImage, std::vector<Tile*> tiles, std::vector<SDL_Rect> tileset);

	private:
		void displayCursor(int x, int y);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *m_screen;

		SDL_Rect camera;
		int m_bgR;
		int m_bgG;
		int m_bgB;
};
#endif
