CXX = clang++
SOURCES = $(wildcard src/*.cpp)
objects = Main.o $(SOURCES:src/%.cpp=%.o)
flagss = -lSDL -lSDL_ttf -lSDL_image -g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG  -Wno-missing-field-initializers -lboost_thread
flags = -g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG  -Wno-missing-field-initializers -std=c++11 -stdlib=libc++

SDL = -framework SDL2 -framework SDL2_ttf -framework SDL2_image
LDFLAGS = $(SDL)
LIBFLAG = -lpthread

all: prgm

prgm : $(objects)
	$(CXX) $(LDFLAGS) $(LIBFLAG) -o prgm $(objects) $(flags)
Main.o : Main.cpp include/Graphics.hpp include/Global.hpp include/Timer.hpp include/Input.hpp
	$(CXX) -c Main.cpp $(flags)
Global.o : include/Global.hpp src/Global.cpp
	$(CXX) -c src/Global.cpp $(flags)
Graphics.o : include/Global.hpp include/Graphics.hpp src/Graphics.cpp include/TextMenu.hpp include/Inventory.hpp
	$(CXX) -c src/Graphics.cpp $(flags)
Timer.o : include/Timer.hpp src/Timer.cpp
	$(CXX) -c src/Timer.cpp $(flags)
Input.o : include/Input.hpp src/Input.cpp
	$(CXX) -c src/Input.cpp $(flags)
StateMachine.o : include/StateMachine.hpp src/StateMachine.cpp include/IState.hpp include/Timer.hpp
	$(CXX) -c src/StateMachine.cpp $(flags)
IntroState.o : include/IntroState.hpp src/IntroState.cpp include/Graphics.hpp include/Global.hpp
	$(CXX) -c src/IntroState.cpp $(flags)
MainMenuState.o : include/MainMenuState.hpp src/MainMenuState.cpp include/Graphics.hpp include/Global.hpp include/TextMenuItem.hpp include/TextMenu.hpp
	$(CXX) -c src/MainMenuState.cpp $(flags)
MenuState.o : include/MenuState.hpp src/MenuState.cpp include/Graphics.hpp include/Global.hpp include/TextMenuItem.hpp include/TextMenu.hpp
	$(CXX) -c src/MenuState.cpp $(flags)
WorldState.o : include/WorldState.hpp src/WorldState.cpp include/Graphics.hpp include/Global.hpp
	$(CXX) -c src/WorldState.cpp $(flags)
# Character.o : include/Character.hpp src/Character.cpp include/Global.hpp
# 	$(CXX) -c src/Character.cpp $(flags)
WorldMap.o : include/WorldMap.hpp src/WorldMap.cpp include/Global.hpp include/Tile.hpp
	$(CXX) -c src/WorldMap.cpp $(flags)
Tile.o : include/Tile.hpp src/Tile.cpp include/Global.hpp
	$(CXX) -c src/Tile.cpp $(flags)
TextMenu.o : include/TextMenu.hpp src/TextMenu.cpp include/Global.hpp
	$(CXX) -c src/TextMenu.cpp $(flags)
TextMenuItem.o : include/TextMenuItem.hpp src/TextMenuItem.cpp include/Global.hpp
	$(CXX) -c src/TextMenuItem.cpp $(flags)
Player.o : include/Player.hpp src/Player.cpp include/Global.hpp
	$(CXX) -c src/Player.cpp $(flags)
NPC.o : include/NPC.hpp src/NPC.cpp include/Global.hpp
	$(CXX) -c src/NPC.cpp $(flags)
Chest.o : include/Chest.hpp src/Chest.cpp include/Global.hpp
	$(CXX) -c src/Chest.cpp $(flags)
Inventory.o : include/Inventory.hpp include/Global.hpp
	$(CXX) -c src/Inventory.cpp $(flags)
LuckyCoin.o : include/LuckyCoin.hpp include/Global.hpp include/IHoldable.hpp
	$(CXX) -c src/LuckyCoin.cpp $(flags)
HealthPotion.o : include/HealthPotion.hpp include/Global.hpp include/IHoldable.hpp
	$(CXX) -c src/HealthPotion.cpp $(flags)
Equipable.o : include/Equipable.hpp include/Global.hpp include/IHoldable.hpp
	$(CXX) -c src/Equipable.cpp $(flags)
Toon.o : include/Toon.hpp include/ISpell.hpp include/Equipable.hpp include/IHoldable.hpp
	$(CXX) -c src/Toon.cpp $(flags)

clean :
	rm *.o
	rm prgm
	rm log

