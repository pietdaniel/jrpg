#include "../include/MainMenuState.hpp"

MainMenuState::MainMenuState(Graphics* g) {
	graphics = g;
	status = true;
	nextState = "world";

	// possibly abstract this into a factory method
	// only problem is in handling callback functions

	// three menu items
	start = new TextMenuItem("New Game","Starts the game",boost::bind(&MainMenuState::start_new_game, this));
	lore = new TextMenuItem("Lore","Posts a description");
	quit = new TextMenuItem("Quit","Exits the game", boost::bind(&MainMenuState::quit_game, this));

	// vector to hold them
	MainMenuV.push_back(*start);
	MainMenuV.push_back(*quit);
	MainMenuV.push_back(*lore);

	// box to draw the menu
	SDL_Rect* box = new SDL_Rect();
	box->x = 300;
	box->y = 400;
	box->w = 300;
	box->h = 100;

	// initialize the menu
	Menu = new TextMenu("Start", "Welcome to my simple game!", MainMenuV, box, true);
	delete box;
	delete start;
	delete lore;
	delete quit;

}

MainMenuState::~MainMenuState() {

}

void MainMenuState::start_new_game() {
	status = false;
}

void MainMenuState::quit_game() {
	SDL_Quit();
}

void MainMenuState::update(Timer* timer, bool* m_keysHeld) {
	if (m_keysHeld[ SDLK_RETURN ] ) {
		Menu->getSelected()->doCallback();
	}

	if (m_keysHeld[ SDLK_DOWN ]) {
		Menu->decSelected();
		m_keysHeld[ SDLK_DOWN ] = false;
	}
	if (m_keysHeld[ SDLK_UP ]) {
		Menu->incSelected();
		m_keysHeld[ SDLK_UP ] = false;
	}

}

void MainMenuState::render() {
	graphics->beginScene();

    graphics->drawText("Main Menu",18,350,350,255,255,255,0,0,0);

    graphics->drawMenu(Menu);

    graphics->endScene();
}

bool MainMenuState::getStatus() {
	return status;
}

void MainMenuState::setStatus(bool s) {
	status = s;
}

std::string MainMenuState::getNextState() {
	return nextState;
}


Player* MainMenuState::getPlayer() {
	return NULL;
}

void MainMenuState::setPlayer(Player* p) {
	// do nothing, compiler complained about pure virtual function
}