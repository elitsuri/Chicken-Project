#include "ThrownObjects.h"



ThrownObjects::ThrownObjects()
{
}


ThrownObjects::~ThrownObjects()
{
}


void ThrownObjects::move(unsigned screenSizeY)
{
	m_sprite.move(sf::Vector2f{ 0, 2 });
	if (m_sprite.getPosition().y > screenSizeY + 5)
		m_available = false;
}
