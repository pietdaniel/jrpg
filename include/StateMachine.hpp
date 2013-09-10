#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP
#include "Timer.hpp"
#include "IState.hpp"
#include <map>
#include <string>

class StateMachine {
	public: 
		StateMachine(std::map<std::string,IState*> states, IState* state);
		~StateMachine();
		void update(bool* m_keysHeld);
		void render();
		void change(std::string key);
		void add(std::string key, IState* state);
		void remove(std::string key);
	private:
		Timer* timer;
		IState* currentState;
		std::map<std::string,IState*> stack;
};
#endif