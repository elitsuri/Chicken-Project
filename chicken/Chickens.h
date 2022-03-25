#pragma once
#include "Enemy.h"
#include "Eggs.h"

class Chickens:public Enemy
{
public:
	Chickens(Resources&, float , float ,unsigned);
	~Chickens() {};
	void move(sf::Time&, sf::Vector2u&, sf::Time&)override;
	void play(Resources& res)override { m_sprite.play(res.getChickenAnimation(0)); }
	void fire(std::vector<std::unique_ptr<ThrownObjects>>&, Resources&, unsigned, sf::Time&)override;
	void show(sf::Time)override;
private:
	unsigned m_position;
};

