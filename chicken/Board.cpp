#include "Board.h"

void Board::create(Resources& res, sf::Vector2u ScreenSize)
{
	m_ship.create(ScreenSize);
	m_chickensCol = ScreenSize.x / 200;
	m_stripLen = (float) ScreenSize.x / m_chickensCol;
	m_chickens.resize(m_chickensCol);
	for (unsigned col = 0; col < m_chickensCol; col++)
	{
		float leftBand = m_stripLen * col,
			rightBand = m_stripLen * (col + 1);
		for (unsigned row = 0; row < m_numOfChickenInRow; row++)
			m_chickens[col].emplace_back(make_unique<Chickens>(res, leftBand, rightBand, row));
	}
	unsigned select = 0;
	for (int i = 0; i < 5; i++)
	{
		auto colindex = res.RandomizeVal(0, (float) m_chickens.size() - 1);
		auto rowindex = res.RandomizeVal(0, (float) m_chickens[colindex].size() - 1);
		m_chickens[colindex][rowindex]->setHoldUpgrade(select + 1);
		select = ((select + 1) % 2);
	}
}

void Board::playAll(Resources &res, Animation* currentAnimation, Time& bossFireTimer)
{
	m_background.play(res.getBackgroundAnimation());
	m_ship.getSprite().play(*currentAnimation);
	if (m_ship.getCrashed())
		m_ship.getExplosionAnimation().play(res.getShipAnimation(4));
	m_boomAnimation.play(res.getBoomAnimation());
	unsigned fire = res.RandomizeVal(1, 1200);
	for (auto &chickensGruop : m_chickens)
	{
		for (auto &chiken : chickensGruop)
		{
			chiken->fire(m_eggs, res, fire, bossFireTimer);
			chiken->play(res);
		}
	}
}

void Board::moveAll(Vector2f &movment, Time &deltaTime,
	RenderWindow &win, Resources &res, Time& showTime)
{
	m_ship.move(win.getSize(), movment, deltaTime.asSeconds());
	for (auto &chickens : m_chickens)
		for (auto &chiken : chickens)
			chiken->move(deltaTime, win.getSize(), showTime);
	for (auto &bullet : m_bullets)
		bullet.move();
	for (auto &object : m_giftsAndUpgrade)
		object->move(win.getSize().y);
	for (auto &egg : m_eggs)
	{
		if (auto eggPtr = static_cast<Eggs*>(egg.get()))
		{
			if (!eggPtr->getBroken())
			{
				egg->move(win.getSize().y);
				if (eggPtr->getPosition().y > win.getSize().y - 35)
					eggPtr->setBrokenAnimation(res, deltaTime);
			}
			else
				eggPtr->sumBrokenTime(deltaTime);
		}
	}
	m_ship.getSprite().stop();
}

void Board::updateAll(sf::Time&frameTime)
{
	Time deltaBackground = milliseconds((int) frameTime.asMilliseconds() * 8);
	Time deltachiken = milliseconds((int) frameTime.asMilliseconds() * 1.5);
	Time deltaexplosion = milliseconds((int) frameTime.asMilliseconds() * 6);
	m_background.update(deltaBackground);
	m_ship.getSprite().update(frameTime);
	if (m_ship.getCrashed())
	{
		m_ship.getExplosionAnimation().update(deltaexplosion);
		if (!m_ship.getExplosionAnimation().isPlaying())
		{
			m_ship.setCrashed(false);
			m_ship.getExplosionAnimation().stop();
		}
	}
	for (auto &chickens : m_chickens)
		for (auto &chiken : chickens)
			chiken->getSprite().update(deltachiken);
}

void Board::drawAll(RenderWindow&win, Resources& res, Time& deltaTime)
{
	win.draw(m_background);
	if (!m_ship.getAvailable())
	{
		m_end = true;
		return;
	}
	m_ship.draw(win);
	sf::Time delta = sf::milliseconds(deltaTime.asMilliseconds() * 10);
	if (m_ship.getExplosionAnimation().isPlaying() && m_ship.getCrashed())
		win.draw(m_ship.getExplosionAnimation());
	else
		m_ship.getExplosionAnimation().play();
	for (auto it = m_boomPlace.begin(); it != m_boomPlace.end();)
	{
		win.draw(m_boomAnimation);
		m_boomAnimation.setPosition(it->x, it->y);
		m_boomAnimation.update(delta);
		m_boomAnimation.setLooped(false);
		if (!m_boomAnimation.isPlaying())
			it = m_boomPlace.erase(it);
		else
			++it;
	}
	for (unsigned row = 0; row < m_chickens.size(); ++row)
	{
		for (unsigned col = 0; col < m_chickens[row].size(); ++col)
		{
			if (!m_chickens[row][col]->getAvailable())
			{
				m_chickens[row].erase(m_chickens[row].begin() + col);
				if (m_bossMode)
				{
					if (m_chickens[0].size() == 0)
					{
						res.getSound(8)->play();
						m_end = true;
						m_win = true;
						return;
					}
				}
			}
			else
				m_chickens[row][col]->draw(win);
		}
	}
	for (auto it = m_bullets.begin(); it != m_bullets.end();)
	{
		if (!it->getAvailable())
			it = m_bullets.erase(it);
		else
		{
			it->draw(win);
			++it;
		}
	}
	for (auto it = m_eggs.begin(); it != m_eggs.end();)
	{
		if ((*it)->getAvailable())
		{
			if (auto eggptr = static_cast<Eggs*>((*it).get()))
			{
				if (eggptr->endBrokenAnimation())
					it = m_eggs.erase(it);
				else
				{
					(*it)->draw(win);
					++it;
				}
			}
		}
		else
			it = m_eggs.erase(it);
	}
	for (auto it = m_giftsAndUpgrade.begin(); it != m_giftsAndUpgrade.end();)
	{
		if (!(*it)->getAvailable())
			it = m_giftsAndUpgrade.erase(it);
		else
		{
			(*it)->draw(win);
			++it;
		}
	}
}
void Board::shipFire(Resources& res, Vector2u screenSize, Time& shipFireTimer)
{
	m_ship.fire(m_bullets, res, screenSize, shipFireTimer);
}

void Board::checkColisions(Resources& res, RenderWindow&win)
{
	for (auto &bullet : m_bullets)
	{
		unsigned index;
		if (m_bossMode)
			index = 0;
		else
			index = bullet.getChickensCol(m_stripLen, m_chickensCol);
		for (auto &chicken : m_chickens[index])
		{
			if (!chicken->getDoneShow())
				continue;
			if (chicken->getSprite().getGlobalBounds().intersects(bullet.getGlobalBounds()))
			{
				m_collisionMangment.processCollision(bullet, *chicken);
				if (!chicken->getAvailable())
				{
					m_boomPlace.emplace_back(chicken->getSprite().getPosition());
					if (chicken->getHoldUpgrade() != 0)
					{
						if (chicken->getHoldUpgrade() == 1)
						{
							m_giftsAndUpgrade.emplace_back(std::make_unique<Upgrade>
								(res, chicken->getSprite().getPosition()));
						}
						else
							m_giftsAndUpgrade.emplace_back(std::make_unique<Gift>
							(res, chicken->getSprite().getPosition()));
					}
				}
			}
		}
	}
	unsigned index;
	if (m_bossMode)
		index = 0;
	else
		index = m_ship.getChickensCol(m_stripLen, m_chickensCol);
	if (index < m_chickens.size() && index >= 0)
	{
		for (auto &chicken : m_chickens[index])
		{
			if (chicken->getSprite().getGlobalBounds().intersects(m_ship.getSprite().getGlobalBounds()))
			{
				m_collisionMangment.processCollision(*chicken, m_ship);
				break;
			}
		}
	}
	auto shipBounds = m_ship.getSprite().getGlobalBounds();
	for (auto &egg : m_eggs)
	{
		if (egg->getGlobalBounds().intersects(shipBounds))
		{
			m_collisionMangment.processCollision(*egg, m_ship);
			m_ship.setCrashed(true);
		}
	}
	for (auto &object : m_giftsAndUpgrade)
		if (object->getGlobalBounds().intersects(shipBounds))
			m_collisionMangment.processCollision(*object, m_ship);
	if (m_ship.getCrashed())
	{
		res.getSound(6)->play();
		m_ship.getExplosionAnimation().setPosition({ m_ship.getSprite().getPosition().x - 20,m_ship.getSprite().getPosition().y - 20 });
		m_ship.getExplosionAnimation().setLooped(false);
	}
}
bool Board::noMoreChicken()
{
	bool ans = true;
	for (auto &v : m_chickens)
		if (v.size() > 0)
			ans = false;
	return ans;
}
void Board::setBoss(Resources &res, Vector2u ScreenSize)
{
	m_chickens[0].emplace_back(std::make_unique<Boss>(res, ScreenSize));
	m_bossMode = true;
}
