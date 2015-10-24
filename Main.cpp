//Daniel Piet Apr 2013
#include "include/Global.hpp"
#include "include/Graphics.hpp"
#include "include/Timer.hpp"
#include "include/Input.hpp"
#include "include/IState.hpp"
#include "include/IntroState.hpp"
#include "include/MainMenuState.hpp"
#include "include/StateMachine.hpp"
#include "include/WorldState.hpp"
#include "include/MenuState.hpp"
#include "include/SpriteBase.hpp"
#include "include/WorldMap.hpp"
#include "include/Tile.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <map>
#include <chrono>
#include <thread>


SDL_Event event;
Graphics* graphics = new Graphics(SCREEN_WIDTH, SCREEN_HEIGHT, "Test Graphics");
Input* input = new Input();

int main( int argc, char* args[] ) {

  IState* mainmenu = new MainMenuState(graphics);

  IState* start = new IntroState(graphics);

  IState* world = new WorldState(graphics);

  IState* menu = new MenuState(graphics);

  std::map<std::string, IState*> myStates;

  StateMachine* myStateMachine = new StateMachine(myStates,start);
  myStateMachine->add("mainmenu",mainmenu);
  myStateMachine->add("world",world);
  myStateMachine->add("menu",menu);

  while( !(input->windowClosed()) ) {
    input->readInput();
    myStateMachine->render();
    myStateMachine->update(input->getInput());
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }

  delete menu;
  delete start;
  delete world;
  delete mainmenu;

  return 0;
}
