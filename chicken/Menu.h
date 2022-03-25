#pragma once
#include <memory>
#include <vector>
#include "Controller.h"

class Command 
{
public:
	virtual ~Command() = default;
	virtual void execute(Controller&) = 0;
};
typedef std::unique_ptr<Command> option;


class Menu 
{
public:
	Menu() {};
	~Menu() {};
	void add(std::unique_ptr<Command> c) 
	{
		m_options.emplace_back(option(std::move(c)));
	}
	void activate(Controller& game);

private:
	std::vector<option> m_options;
	void drawAll(Controller& game);
	void setCursor(Controller&, sf::Vector2f);
	void setTexts(Controller&);
	void setBackground(Controller&);
	void makeScreen(Controller&);
};
