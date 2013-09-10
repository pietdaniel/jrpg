#ifndef WORLDMAP_HPP
#define WORLDMAP_HPP
#include "Global.hpp"
#include "Tile.hpp"
#include <vector>
#include <string>
#include <fstream>

class WorldMap {
	public:
		WorldMap(int w, int h);
		~WorldMap();
		bool loadMap(char* file, int TOTAL_TILES, int TILE_SPRITES, int tileWidth, int tileHeight);
		std::vector<Tile*> getTiles();
		int getLevelWidth();
		int getLevelHeight();

	private:
		int LEVEL_WIDTH;
		int LEVEL_HEIGHT;
		int TILE_SPRITES;
		std::vector<Tile*> tiles;

};
#endif