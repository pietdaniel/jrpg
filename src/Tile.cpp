#include "../include/Tile.hpp"

Tile::Tile(int x, int y, int width, int height, int t) {
	box.x = x;
	box.y = y;
	box.w = width;
	box.h = height;
	type = t;
}

Tile::~Tile() {

}

SDL_Rect Tile::getBox() {
	return box;
}

int Tile::getType() {
	return type;
}