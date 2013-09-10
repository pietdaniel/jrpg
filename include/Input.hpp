#ifndef INPUT_HPP
#define INPUT_HPP
#include "SDL/SDL.h"
#include "Global.hpp"

class Input {
	public:
		Input();
		~Input();

		void readInput();

		bool* getInput();

		bool windowClosed();

	private:
		SDL_Event m_event;
		bool m_keysHeld[323];
		bool m_windowClosed;
};
#endif
