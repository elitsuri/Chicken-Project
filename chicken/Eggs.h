#pragma once
#include "ThrownObjects.h"
#include<SFML\Graphics\Rect.hpp>

class Eggs:
	public ThrownObjects
{
public:
	Eggs(Resources& res, const sf::FloatRect& chikenBounds, const sf::Vector2f& chickenPos)
	{
		m_sprite.setAnimation(res.getEggAnimation(0));
		res.getSound(2)->play();
		m_sprite.setPosition({ chickenPos.x + chikenBounds.width / 2 ,chickenPos.y + chikenBounds.height + 0 });
	}
	~Eggs() {};
	bool getBroken()const { return  m_isBroken; }
	void setBrokenAnimation(Resources& res, sf::Time& tm)
	{
		m_brokenTime = m_endAnimaition += tm;
		m_sprite.setAnimation(res.getEggAnimation(1));
		res.getSound(3)->play();
		m_isBroken = true;
	}
	void sumBrokenTime(sf::Time &tm) { m_endAnimaition += tm; }
	bool endBrokenAnimation()const { return m_endAnimaition.asSeconds() - m_brokenTime.asSeconds() > 1.5; }
private:
	sf::Time m_brokenTime = sf::seconds(0),
		m_endAnimaition = sf::seconds(0);
	bool m_isBroken = false;
};
