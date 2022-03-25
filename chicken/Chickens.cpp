#include "Chickens.h"

Chickens::Chickens(Resources&res, float left, float right, unsigned row)
	:Enemy{ left, right, res, 3 }
{
	m_fire = res.RandomizeVal(1, 1200);
	m_position = res.RandomizeVal(m_leftBand + 10, m_rightBand - 110);
	m_sprite.setPosition(sf::Vector2f(-100, row * 85));
	m_sprite.setAnimation(res.getChickenAnimation(0));
	m_pakpak = res.getSound(1);
}

void Chickens::move(sf::Time& frameTime, sf::Vector2u& screenSize, sf::Time& showTime)
{
	if (!m_doneShow)
	{
		show(frameTime);
		return;
	}
	if (m_right)
		m_movementChiken.x += 50.f;
	else
		m_movementChiken.x -= 50.f;
	if (abs(m_sprite.getPosition().x - m_leftBand) < 5.f)
		m_right = true;
	if (abs(m_sprite.getPosition().x + 100 - m_rightBand) < 5.f)
		m_right = false;
	if (showTime.asSeconds() > 7)
		m_movementChiken.y += 25;
	m_sprite.move(m_movementChiken * frameTime.asSeconds());
	m_movementChiken.x = 0;
	m_movementChiken.y = 0;
	if (m_sprite.getPosition().y > screenSize.y + 0)
		m_sprite.setPosition(m_sprite.getPosition().x, -90.f);
}

void Chickens::fire(std::vector<std::unique_ptr<ThrownObjects>>& eggs, Resources &res, unsigned fire, sf::Time&)
{
	if (m_doneShow && fire == m_fire)
		eggs.emplace_back(std::make_unique <Eggs>(res, m_sprite.getGlobalBounds(), m_sprite.getPosition()));
}

void Chickens::show(sf::Time deltaTime)
{
	m_movementChiken.x += 2;
	m_sprite.move(m_movementChiken * deltaTime.asSeconds());
	if (abs(m_sprite.getPosition().x + 100 - m_position) < 10.f)
		m_doneShow = true;
}