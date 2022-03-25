#pragma once
#include "ThrownObjects.h"
#include <SFML/Graphics.hpp>


class Gift :
	public ThrownObjects
{
public:
	Gift(Resources &res, const sf::Vector2f &chickenPosition)
	{
		m_sprite.setAnimation(res.getGiftAnimation());
		m_sprite.setPosition({ chickenPosition.x + 50, chickenPosition.y + 120 });
	}
	~Gift() {};
};

