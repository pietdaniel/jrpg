#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP
#include "IState.hpp"
#include "TextMenuItem.hpp"
#include "TextMenu.hpp"
#include "Global.hpp"
#include "Player.hpp"
#include <vector>
#include "boost/function.hpp"
#include "boost/bind.hpp"

class MainMenuState : public IState {
	public:
		MainMenuState(Graphics* g);
		~MainMenuState();
		
		virtual void update(Timer* timer, bool* m_keysHeld);
		virtual void render();
		virtual bool getStatus();
		virtual void setStatus(bool s);
		virtual std::string getNextState();

		virtual void setPlayer(Player* p);
		virtual Player* getPlayer();

		void start_new_game();
		void quit_game();
		

	private:
		Graphics* graphics;
		bool status;
		std::string nextState;

		TextMenuItem* start;
		TextMenuItem* quit;
		TextMenuItem* lore;
		TextMenuItem* MainMenu;
		std::vector<TextMenuItem> MainMenuV;
		TextMenu* Menu;


};
#endif