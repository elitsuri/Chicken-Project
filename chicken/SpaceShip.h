#pragma once
#include "GameObject.h"
#include "Bullets.h"
class ThrownObjects;
class SpaceShip:public GameObject
{
public:
	SpaceShip();
	~SpaceShip() {};
	unsigned getChickensCol(float stripLen, int numOfCol) const;
	void move(sf::Vector2u&,sf::Vector2f& , float );
	void create( sf::Vector2u );
	void fire(std::vector<Bullets>&, Resources&, sf::Vector2u, sf::Time&)const;
	AnimatedSprite& getExplosionAnimation() { return m_explosion; }
	void setExplositionAnimation(Animation&anim) { m_explosion.setAnimation(anim); }
	void decreaseLive();
	void setCrashed(bool val) { m_Crashed = val; }
	bool getCrashed()const { return m_Crashed; }
	unsigned getLives()const { return m_lives; }
	void speedFire() { m_fireSpeed -= sf::seconds((float)0.085); }
	void setLevelUpFire() { m_fireLevel++; }
	bool getLevelUpFire()const { return  m_fireLevel; }
	void resetShipWeapon();
	void show(sf::Vector2u& ,float);
private:
	unsigned m_fireLevel = 0;
	bool m_Crashed = false;
	bool m_doneShow = false;
	unsigned m_lives;
	sf::Vector2u m_screenSize;
	sf::Time m_fireSpeed = sf::seconds((float)0.36) ;
	AnimatedSprite m_explosion;
};