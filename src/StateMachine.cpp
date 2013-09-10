#include "../include/StateMachine.hpp"
#include <map>
#include <string>

StateMachine::StateMachine(std::map<std::string,IState*> states, IState* state) {
	timer = new Timer();
	timer->start();
	currentState = state;
	stack=states;
}
StateMachine::~StateMachine() {
	timer->stop();
}
void StateMachine::update(bool* m_keysHeld) {
	if (!currentState->getStatus()) {
		stack.at(currentState->getNextState())->setStatus(true);
		if (currentState->getNextState() == "menu") {
			stack.at(currentState->getNextState())->setPlayer(currentState->getPlayer());
		}
		currentState = stack.at(currentState->getNextState());
	}
	currentState->update(timer, m_keysHeld);
}
void StateMachine::render() {
	currentState->render();
}
void StateMachine::change(std::string key) {
	currentState = stack.at(key);
}
void StateMachine::add(std::string key, IState* state) { 
	stack[key]=state;
}

void StateMachine::remove(std::string key) {
	stack.erase(key);
}