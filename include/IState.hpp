#ifndef ISTATE_HPP
#define ISTATE_HPP
#include "IState.hpp" // fixme is this necessary
#include "Timer.hpp"
#include "Graphics.hpp"
#include "Player.hpp"
#include <string>

class IState {
	public:
		virtual void update(Timer* timer, bool* m_keysHeld) = 0;
		virtual void render() = 0;
		virtual bool getStatus() = 0;
		virtual std::string getNextState() = 0;
		virtual void setStatus(bool s) = 0;
		virtual void setPlayer(Player* p) = 0;
		virtual Player* getPlayer() = 0;
	private:
		bool status;
		std::string nextState;
};
#endif