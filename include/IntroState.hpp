#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP
#include "IState.hpp"
#include "Global.hpp"
#include "Player.hpp"
#include <vector>

class IntroState : public IState {
	public:
		IntroState(Graphics* g);
		~IntroState();
		
		virtual void update(Timer* timer, bool* m_keysHeld);
		virtual void render();
		virtual bool getStatus();
		virtual std::string getNextState();
		virtual void setStatus(bool s);

		virtual void setPlayer(Player* p);
		virtual Player* getPlayer();
	private:
		SDL_Surface* wizardBitmap;
		SDL_Surface* dragonBitmap;
		SDL_Surface* titleBitmap;
		Graphics* graphics;
		int dragonX;
		int dragonY;

		bool status;
		std::string nextState;
};
#endif