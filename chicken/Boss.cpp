#include "Boss.h"


Boss::Boss(Resources&res, sf::Vector2u& screenSize)
	:Enemy { 0.f,screenSize.x, res, 100 }
{
	m_fireTime = sf::seconds(0.6);
	m_sprite.setAnimation(res.getBossAnimation());
	m_pakpak = res.getSound(7);
	m_sprite.setPosition(sf::Vector2f(screenSize.x / 2 - 150, -350));
}

void Boss::move(sf::Time &deltaTime, sf::Vector2u &screenSize, sf::Time&)
{
	if (!m_doneShow)
	{
		show(deltaTime);
		return;
	}
	if (m_right)
		m_movementChiken.x += 100.f;
	else
		m_movementChiken.x -= 75.f;
	if (abs(m_sprite.getPosition().x - m_leftBand) < 5.f)
		m_right = true;
	if (abs(m_sprite.getPosition().x + 300 - m_rightBand) < 5.f)
		m_right = false;
	if (m_up)
		m_movementChiken.y -= 40;
	else
		m_movementChiken.y += 50;
	if (abs(m_sprite.getPosition().y - screenSize.y) < 300.f)
		m_up = true;
	if (abs(m_sprite.getPosition().y) < 5.f)
		m_up = false;
	m_sprite.move(m_movementChiken * (2.f * deltaTime.asSeconds()));
	m_movementChiken.x = 0;
	m_movementChiken.y = 0;
}

void Boss::fire(std::vector<std::unique_ptr<ThrownObjects>>&eggs, Resources&res, unsigned, sf::Time& bossFireTime)
{
	if (!m_doneShow)
		return;
	if (bossFireTime.asSeconds() >= m_fireTime.asSeconds())
	{
		eggs.emplace_back(std::make_unique <Eggs>(res, m_sprite.getGlobalBounds(), m_sprite.getPosition()));
		bossFireTime = sf::milliseconds(0);
	}
}

void Boss::show(sf::Time deltaTime)
{
	m_movementChiken.y += 1;
	m_sprite.move(m_movementChiken * deltaTime.asSeconds());
	if (m_sprite.getPosition().y > 200)
		m_doneShow = true;
}