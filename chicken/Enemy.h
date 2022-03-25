#pragma once
#include <SFML/Audio/Sound.hpp>
#include "GameObject.h"
#include "ThrownObjects.h"

class Enemy:public GameObject
{
public:
	Enemy(float left, float right, Resources&, unsigned lives)
		:m_leftBand(left), m_rightBand(right), m_movementChiken(0, 0), m_lives(lives) {}
	virtual ~Enemy() {};
	virtual void move(sf::Time&, sf::Vector2u&, sf::Time&) = 0;
	virtual void fire(std::vector<std::unique_ptr<ThrownObjects>>&, Resources&, unsigned, sf::Time&) = 0;
	virtual void play(Resources&) = 0;
	virtual void show(sf::Time) = 0;
	void decreaseLife()
	{
		m_lives--;
		if (m_lives == 0)
			m_available = false;
	}
	void playPakPak()const { m_pakpak->play(); }
	auto getHoldUpgrade()const { return m_holdUpgrade; }
	void setHoldUpgrade(unsigned i) { m_holdUpgrade = i; }
	
	auto getDoneShow() { return m_doneShow; }
protected:
	float m_leftBand;
	float m_rightBand;
	bool m_right = true;
	bool m_doneShow = false;
	unsigned m_lives;
	unsigned m_fire;
	unsigned m_holdUpgrade = 0;
	sf::Vector2f m_movementChiken;
	sf::Sound* m_pakpak = nullptr;
};