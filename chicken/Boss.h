#pragma once

#include "Eggs.h"
#include "Enemy.h"

class Boss :public Enemy
{
public:
	Boss(Resources&, sf::Vector2u& );
	~Boss() {};
	void move(sf::Time&, sf::Vector2u&, sf::Time&)override;
	void fire(std::vector<std::unique_ptr<ThrownObjects>>&, Resources&, unsigned, sf::Time&) override;
	void show(sf::Time)override;
	void play(Resources&res)override { m_sprite.play(res.getBossAnimation()); }
private:
	sf::Time m_fireTime;
	bool m_up = false;
};

