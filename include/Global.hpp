//JRPG Daniel Piet Apr 2013
#ifndef GLOBAL_HPP
#define GLOBAL_HPP
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_BPP;
extern std::vector<int> ARROW_KEY_STACK;
// fixme not best way
// extern const std::string PLAYER_DIR_KEY[16];
bool check_collision( SDL_Rect A, SDL_Rect B );
#endif
