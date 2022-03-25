#pragma once
#include "AnimatedSprite.h"
#include "Resources.h"
#include <SFML/Graphics/RenderWindow.hpp>


namespace sf
{
	class Time;
	class RenderWindow;
}

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};
	virtual void draw(sf::RenderWindow& win) { win.draw(m_sprite); }
	void setAnimation(Animation& animation) { m_sprite.setAnimation(animation); }
	AnimatedSprite& getSprite() { return m_sprite; }
	auto getPosition()const { return m_sprite.getPosition(); }
	auto getGlobalBounds() const { return m_sprite.getGlobalBounds(); }
	auto getAvailable() const { return m_available; }
	void setUnAvailable() { m_available = false; }
protected:
	AnimatedSprite m_sprite;
	bool m_available = true;
};

