
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#else		
#error "Unrecognized configuration!"
#endif

#include "Controller.h"
#include "Windows.h"

using namespace sf;

void Controller::play()
{
	m_board.create(m_resources, m_window.getSize());
	Clock gameClock;
	Time shipFireTimer = milliseconds(0);
	Time bossFireTimer = milliseconds(0);
	Time showTime = milliseconds(0);
	bool noKeyWasPressed = true;
	float speed = 250; 
	Animation* currentShipAnimation = &m_resources.getShipAnimation(1);
	while (m_window.isOpen())
	{
		Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				m_window.close();
				exit(EXIT_SUCCESS);
			}
			if (event.key.code == Keyboard::Escape)
			{
				m_window.close();
				exit(EXIT_SUCCESS);
			}
		}
		Time deltaTime = gameClock.restart();
		shipFireTimer += deltaTime;
		bossFireTimer += deltaTime;
		showTime += deltaTime;
		Vector2f movement(0.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::Space))
			m_board.shipFire(m_resources, m_window.getSize(), shipFireTimer);
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			currentShipAnimation = &m_resources.getShipAnimation(0);
			movement.y -= speed;
			noKeyWasPressed = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			currentShipAnimation = &m_resources.getShipAnimation(1);
			movement.y += speed;
			noKeyWasPressed = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{

			currentShipAnimation = &m_resources.getShipAnimation(2);
			movement.x -= speed;
			noKeyWasPressed = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			currentShipAnimation = &m_resources.getShipAnimation(3);
			movement.x += speed;
			noKeyWasPressed = false;
		}
		m_board.playAll(m_resources, currentShipAnimation, bossFireTimer);
		m_resources.setPositionForCurser(m_window);
		m_board.moveAll(movement, deltaTime, m_window, m_resources, showTime);
		m_board.checkColisions(m_resources, m_window);
		if (noKeyWasPressed)
			m_board.resetShip(m_resources);
		noKeyWasPressed = true;
		m_board.updateAll(deltaTime);
		m_board.drawAll(m_window, m_resources, deltaTime);
		m_window.display();
		if (!m_bossMode && m_board.noMoreChicken())
		{
			m_board.setBoss(m_resources, m_window.getSize());
			m_bossMode = true;
		}
		if (m_board.getEnd())
			endGame();
	}
}

void Controller::endGame()
{
	Sprite back;	
	Clock ck;
	if (m_board.getWin())
		back.setTexture(*m_resources.getSpriteSheet(14));
	else 
	{
		m_resources.getSound(5)->play();
		back.setTexture(*m_resources.getSpriteSheet(13));
	}
	float ScaleX = (float)m_window.getSize().x / m_resources.getSpriteSheet(14)->getSize().x;
	float ScaleY = (float)m_window.getSize().y / m_resources.getSpriteSheet(14)->getSize().y;
	back.setScale(ScaleX, ScaleY);
	while (ck.getElapsedTime().asSeconds() < 5)
	{
		m_window.clear();
		m_window.draw(back);
		m_window.display();
	}
	exit(EXIT_SUCCESS);
}