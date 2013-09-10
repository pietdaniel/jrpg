#include "../include/IntroState.hpp"

IntroState::IntroState(Graphics* g) {
	graphics = g;
	wizardBitmap = graphics->loadBitmap("build/wizard.bmp",0,255,255);
	dragonBitmap = graphics->loadBitmap("build/dragon.bmp",0,255,255);
	titleBitmap = graphics->loadBitmap("build/title.bmp",0,255,255);
	dragonX = -400;
	dragonY = 100;
	status = true;
	nextState = "mainmenu";

}

void IntroState::setStatus(bool s) {
	status = s;
}

IntroState::~IntroState() {
	graphics->endScene();
	graphics->closeBitmap(wizardBitmap);
	graphics->closeBitmap(dragonBitmap);
	graphics->closeBitmap(titleBitmap);
	delete graphics;
}

void IntroState::update(Timer* timer, bool* m_keysHeld) {
    if (dragonX < 0 && timer->get_ticks() > 1000) {
		dragonX+=5;
    }
    if (timer->get_ticks()> 2500 || m_keysHeld[ SDLK_RETURN ]) {
    	m_keysHeld[ SDLK_RETURN ] = false;
    	status = false;
    }
}

void IntroState::render() {
	graphics->beginScene();

	graphics->drawSprite(titleBitmap,0,0,0,0,700,700);

    graphics->drawSprite(wizardBitmap,0,0,500,450,200,200);

	graphics->drawSprite(dragonBitmap,0,0,dragonX,dragonY,400,400);

    graphics->drawText("Welcome to my god damn JRPG",18,10,10,255,255,255,0,0,0);
	
    graphics->endScene();
}

bool IntroState::getStatus() {
	return status;
}

std::string IntroState::getNextState() {
	return nextState;
}

Player* IntroState::getPlayer() {
	return NULL;
}

void IntroState::setPlayer(Player* p) {
	// do nothing, compiler complained about pure virtual function
}