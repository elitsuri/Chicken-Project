#include "Menu.h"
#include <fstream>
#include "FileNotOpenEx.h"
#include <iostream>
void Menu::activate(Controller & game)
{
	makeScreen(game);
	sf::View fixed = game.getWindow().getView();
	setBackground(game);
	setTexts(game);

	for (sf::Event event; game.getWindow().waitEvent(event);)
	{
		if (game.getRes().getSound(4)->getStatus() == sf::SoundSource::Stopped)
			game.getRes().getSound(4)->play();
		if (event.key.code == sf::Keyboard::Escape)
		{
			game.getWindow().close();
			m_options[1]->execute(game);
		}
		sf::Vector2f mappedMousePosition =
			game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow()));

		switch (event.type)
		{
			case sf::Event::MouseButtonReleased:

				if (game.getRes().getText(0)->getGlobalBounds().contains(mappedMousePosition))
				{
					game.getRes().getSound(4)->stop();
					m_options[0]->execute(game);//play
				}
				if (game.getRes().getText(1)->getGlobalBounds().contains(mappedMousePosition))
				{
					m_options[1]->execute(game);//exit
					break;
				}
				if (game.getRes().getText(2)->getGlobalBounds().contains(mappedMousePosition))
				{
					m_options[2]->execute(game);//help
					break;
				}
		}
		setCursor(game, mappedMousePosition);
		game.getRes().setPositionForCurser(game.getWindow());
		game.getWindow().clear();
		game.getWindow().setView(fixed);
		drawAll(game);
		game.getWindow().display();
	}
}

void Menu::drawAll(Controller& game)
{
	game.getWindow().draw(*game.getRes().getMenuAnimation());
	game.getWindow().draw(*game.getRes().getText(0));
	game.getWindow().draw(*game.getRes().getText(1));
	game.getWindow().draw(*game.getRes().getText(2));
	game.getWindow().draw(*game.getRes().getCurserAnimation());
}

void Menu::setCursor(Controller& game, sf::Vector2f mappedMousePosition)
{
	if (game.getRes().getText(0)->getGlobalBounds().contains(mappedMousePosition) ||
		game.getRes().getText(1)->getGlobalBounds().contains(mappedMousePosition) ||
		game.getRes().getText(2)->getGlobalBounds().contains(mappedMousePosition))
		game.getRes().getCurserAnimation()->setTexture(*game.getRes().getSpriteSheet(8));
	else
		game.getRes().getCurserAnimation()->setTexture(*game.getRes().getSpriteSheet(6));
}

void Menu::setTexts(Controller& game)
{
	game.getRes().getText(0)->setString("Play");
	game.getRes().getText(0)->setPosition((float)(game.getWindow().getSize().x / 2.3)
										  , (float)(game.getWindow().getView().getSize().y / 3.3));
	game.getRes().getText(1)->setString("Exit");
	game.getRes().getText(1)->setPosition((float)(game.getWindow().getView().getSize().x / 2.3)
										  , (float)(game.getWindow().getView().getSize().y / 2.3) + 220);
	game.getRes().getText(2)->setString("Help");
	game.getRes().getText(2)->setPosition((float)(game.getWindow().getView().getSize().x / 2.3)
										  , (float)(game.getWindow().getView().getSize().y / 2.3) + 40);
}

void Menu::setBackground(Controller& game)
{
	game.getRes().getMenuAnimation()->setScale(game.getWindow().getView().getSize().x
											   / game.getRes().getMenuAnimation()->getLocalBounds().width,
											   game.getWindow().getView().getSize().y
											   / game.getRes().getMenuAnimation()->getLocalBounds().height);
}

void Menu::makeScreen(Controller& game)
{
	auto mode = sf::VideoMode::getFullscreenModes();
	game.getWindow().create(mode[0], "Chiken invaders!", sf::Style::Fullscreen);
	game.getWindow().setMouseCursorVisible(false);
	game.getWindow().setFramerateLimit(60);
}
//-------------------------------classes----------------------------------
class Play : public Command
{
public:
	void execute(Controller& game)override
	{
		game.play();
	}
};

class Exit : public Command
{
public:
	void execute(Controller&game)override
	{
		exit(EXIT_SUCCESS);
	}
};

class Help : public Command
{
public:
	void execute(Controller&game)override
	{
		sf::View fixed = game.getWindow().getView();
		for (sf::Event event; game.getWindow().waitEvent(event);)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				game.getWindow().close();
				exit(EXIT_SUCCESS);
			}
			sf::Vector2f mappedMousePosition =
				game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow()));

			switch (event.type)
			{
				case sf::Event::MouseButtonReleased:
					if (game.getRes().getText(4)->getGlobalBounds().contains(mappedMousePosition))
						return;
			}
			//------------read help from file------------
			std::ifstream ifs("help.txt");
			std::string content((std::istreambuf_iterator<char>(ifs)),
				(std::istreambuf_iterator<char>()));
			//-------------------------------------------
			game.getRes().getText(3)->setString(content);
			//-----------------------------------------
			game.getRes().getText(4)->setString("Back");
			//-------------------set postion reletive to screen--------
			game.getRes().getText(3)->setPosition((float)(game.getWindow().getView().getSize().x / 8)
												  , (float)(game.getWindow().getView().getSize().y / 3));
			game.getRes().getText(4)->setPosition(((float)game.getWindow().getSize().x) - 200
												  , (float)(game.getWindow().getSize().y) - 90);
			//------------------curser manegment---------------------
			game.getRes().setPositionForCurser(game.getWindow());
			if (game.getRes().getText(4)->getGlobalBounds().contains(mappedMousePosition))
				game.getRes().getCurserAnimation()->setTexture(*game.getRes().getSpriteSheet(8));
			else
				game.getRes().getCurserAnimation()->setTexture(*game.getRes().getSpriteSheet(6));
			//-----------------------------------------------------
			game.getWindow().clear();
			game.getWindow().setView(fixed);
			game.getWindow().draw(*game.getRes().getMenuAnimation());
			game.getWindow().draw(*game.getRes().getText(3));
			game.getWindow().draw(*game.getRes().getText(4));
			game.getWindow().draw(*game.getRes().getCurserAnimation());
			game.getWindow().display();
		}
	}
};
//------------------------------------------------------------------
int main()
{
	try
	{
		Controller game;
		Menu m;
		m.add(std::make_unique<Play>());
		m.add(std::make_unique<Exit>());
		m.add(std::make_unique<Help>());
		game.getRes().getSound(4)->play();
		m.activate(game);
	}
	catch (FileNotOpenEx&)
	{
		std::cout << "problem in resorces, file not open\n";
		exit(EXIT_FAILURE);
	}
}