SOURCES = $(wildcard src/*.cpp)
objects = Main.o $(SOURCES:src/%.cpp=%.o) 
flags = -lSDL -lSDL_ttf -lSDL_image -g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG  -Wno-missing-field-initializers -lboost_thread

all: prgm

prgm : $(objects)
	g++ -o prgm $(objects) $(flags)
Main.o : Main.cpp include/Graphics.hpp include/Global.hpp include/Timer.hpp include/Input.hpp
	g++ -c Main.cpp $(flags)
Global.o : include/Global.hpp src/Global.cpp
	g++ -c src/Global.cpp $(flags)
Graphics.o : include/Global.hpp include/Graphics.hpp src/Graphics.cpp include/TextMenu.hpp include/Inventory.hpp
	g++ -c src/Graphics.cpp $(flags)
Timer.o : include/Timer.hpp src/Timer.cpp
	g++ -c src/Timer.cpp $(flags)
Input.o : include/Input.hpp src/Input.cpp
	g++ -c src/Input.cpp $(flags)
StateMachine.o : include/StateMachine.hpp src/StateMachine.cpp include/IState.hpp include/Timer.hpp
	g++ -c src/StateMachine.cpp $(flags)
IntroState.o : include/IntroState.hpp src/IntroState.cpp include/Graphics.hpp include/Global.hpp
	g++ -c src/IntroState.cpp $(flags)
MainMenuState.o : include/MainMenuState.hpp src/MainMenuState.cpp include/Graphics.hpp include/Global.hpp include/TextMenuItem.hpp include/TextMenu.hpp
	g++ -c src/MainMenuState.cpp $(flags)
MenuState.o : include/MenuState.hpp src/MenuState.cpp include/Graphics.hpp include/Global.hpp include/TextMenuItem.hpp include/TextMenu.hpp
	g++ -c src/MenuState.cpp $(flags)
WorldState.o : include/WorldState.hpp src/WorldState.cpp include/Graphics.hpp include/Global.hpp
	g++ -c src/WorldState.cpp $(flags)
# Character.o : include/Character.hpp src/Character.cpp include/Global.hpp
# 	g++ -c src/Character.cpp $(flags)
WorldMap.o : include/WorldMap.hpp src/WorldMap.cpp include/Global.hpp include/Tile.hpp
	g++ -c src/WorldMap.cpp $(flags)
Tile.o : include/Tile.hpp src/Tile.cpp include/Global.hpp
	g++ -c src/Tile.cpp $(flags)
TextMenu.o : include/TextMenu.hpp src/TextMenu.cpp include/Global.hpp
	g++ -c src/TextMenu.cpp $(flags)
TextMenuItem.o : include/TextMenuItem.hpp src/TextMenuItem.cpp include/Global.hpp
	g++ -c src/TextMenuItem.cpp $(flags)
Player.o : include/Player.hpp src/Player.cpp include/Global.hpp
	g++ -c src/Player.cpp $(flags)
NPC.o : include/NPC.hpp src/NPC.cpp include/Global.hpp
	g++ -c src/NPC.cpp $(flags)
Chest.o : include/Chest.hpp src/Chest.cpp include/Global.hpp
	g++ -c src/Chest.cpp $(flags)
Inventory.o : include/Inventory.hpp include/Global.hpp
	g++ -c src/Inventory.cpp $(flags)
LuckyCoin.o : include/LuckyCoin.hpp include/Global.hpp include/IHoldable.hpp
	g++ -c src/LuckyCoin.cpp $(flags)
HealthPotion.o : include/HealthPotion.hpp include/Global.hpp include/IHoldable.hpp
	g++ -c src/HealthPotion.cpp $(flags)
Equipable.o : include/Equipable.hpp include/Global.hpp include/IHoldable.hpp
	g++ -c src/Equipable.cpp $(flags)
Toon.o : include/Toon.hpp include/ISpell.hpp include/Equipable.hpp include/IHoldable.hpp
	g++ -c src/Toon.cpp $(flags)

clean :
	rm *.o
	rm prgm
	rm log

