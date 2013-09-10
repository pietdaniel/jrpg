#ifndef TILE_HPP
#define TILE_HPP
#include "Global.hpp"

class Tile {
	public:
		Tile(int x, int y, int width, int height, int t);
		~Tile();
		SDL_Rect getBox();
		int getType();
	private:
		SDL_Rect box;
		int type;

};
#endif