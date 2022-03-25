#include "SpaceShip.h"



SpaceShip::SpaceShip()
	:m_lives(4)
{
	m_sprite.pause();
	m_sprite.setLooped(false);
}


unsigned SpaceShip::getChickensCol(float stripLen, int numOfCol) const
{
	float x = m_sprite.getPosition().x;

	for (int i = 0; i< numOfCol; i++)
	{
		if (x >= i*stripLen && x < (i + 1)* stripLen) 
			return i;
	}
	return 0;
}



void SpaceShip::move(sf::Vector2u&Screen, sf::Vector2f& dirc, float frameTime)
{
	if (!m_doneShow)
	{
		show(Screen, frameTime);
		return;
	}

	m_sprite.move(dirc * frameTime);
	if (m_sprite.getPosition().y + 80 > Screen.y || 
		m_sprite.getPosition().y < 25 ||
		m_sprite.getPosition().x < 5 ||
		m_sprite.getPosition().x > Screen.x - 40)
		m_sprite.move(-dirc * frameTime);
}

void SpaceShip::create(sf::Vector2u winSize)
{
	m_sprite.setPosition(sf::Vector2f((float)winSize.x / 2, (float)winSize.y + 20 ));
	m_screenSize = winSize;
}
void SpaceShip::fire(std::vector<Bullets>&bulletV, Resources &res, sf::Vector2u screenSize, sf::Time& shipFireTimer)const
{
	if (shipFireTimer.asSeconds() >= m_fireSpeed.asSeconds()) 
	{
		Bullets blt{ res, m_sprite.getPosition() };
		if (m_fireLevel == 1)
		{
			blt.getSprite().setAnimation(res.getBulletsAnimations(1));
			blt.getSprite().setPosition(m_sprite.getPosition().x + 5, m_sprite.getPosition().y);
		}
		if (m_fireLevel == 2)
		{
			blt.getSprite().setPosition(m_sprite.getPosition().x - 5, m_sprite.getPosition().y);
			blt.getSprite().setAnimation(res.getBulletsAnimations(2));
		}
		res.getSound(0)->play();
		bulletV.emplace_back(blt);
		shipFireTimer = sf::milliseconds(0);
	}
}
void SpaceShip::decreaseLive()
{
	--m_lives;
	m_Crashed = true;
	if (m_lives == 0)
		m_available = false;
}

void SpaceShip::resetShipWeapon()
{
	m_fireLevel = 0; 
	m_fireSpeed = sf::seconds((float)0.45);
	m_sprite.setPosition({ float(m_screenSize.x/2),float(m_screenSize.y-100 )});
}

void SpaceShip::show(sf::Vector2u&Screen, float frameTime)
{
	sf::Vector2f move{ 0.f,-8.f };
	m_sprite.move(3 * frameTime * move);
	if (m_sprite.getPosition().y < Screen.y - 110)
		m_doneShow = true;
}