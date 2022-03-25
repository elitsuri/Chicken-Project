#pragma once
#include "Board.h"
#include "Resources.h"
#include "colission.h"

class Controller
{
public:
	Controller() {};
	~Controller() {};
	void play();
	void endGame();
	sf::RenderWindow &getWindow() { return m_window; }
	Resources& getRes() { return m_resources; }
private:
	Resources m_resources;
	Board m_board;
	sf::RenderWindow m_window;
	bool m_bossMode = false;
};

