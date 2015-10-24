#include "../include/WorldMap.hpp"

WorldMap::WorldMap(int w, int h) {
  LEVEL_WIDTH = w;
  LEVEL_HEIGHT = h;
}

WorldMap::~WorldMap() {

}

bool WorldMap::loadMap(char* file, int TOTAL_TILES, int TILE_SPRITES, int tileWidth, int tileHeight) {
  //The tile offsets
  int x = 0, y = 0;

  //Open the map
  std::ifstream input( file );

  //If the map couldn't be loaded
  // TODO resolve this
  //if (input == nullptr) {
    //printf("Could not load the map\n");
    //printf("%s\n", file);
    //return false;
  //}

  //Initialize the tiles
  for( int t = 0; t < TOTAL_TILES; t++ ) {
    //Determines what kind of tile will be made
    int tileType = -1;

    //Read tile from map file
    input >> tileType;

    //If the was a problem in reading the map
    if( input.fail() == true )
    {
      //Stop loading map
      printf("Problem Reading the map\n");
      input.close();
      return false;
    }

    //If the number is a valid tile number
    if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) )
    {
      tiles.push_back(new Tile( x, y, tileWidth, tileHeight, tileType ));
    }
    //If we don't recognize the tile type
    else
    {
      printf("Unrecognized filetype\n");
      //Stop loading map
      input.close();
      return false;
    }

    //Move to next tile spot
    x += tileWidth;

    //If we've gone too far
    if( x >= LEVEL_WIDTH )
    {
      //Move back
      x = 0;

      //Move to the next row
      y += tileHeight;
    }
  }

  //Close the file
  input.close();

  //If the map was loaded fine
  return true;

}

std::vector<Tile*> WorldMap::getTiles() {
  return tiles;
}
int WorldMap::getLevelWidth() {
  return LEVEL_WIDTH;
}
int WorldMap::getLevelHeight() {
  return LEVEL_HEIGHT;
}
