#pragma once
#ifndef ANIMATION_INCLUDE
#define ANIMATION_INCLUDE
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

class Animation
{
public:
	Animation():m_texture(NULL) {};
	void addFrame(sf::IntRect rect) { m_frames.push_back(rect); }
	void setSpriteSheet(const sf::Texture& texture) { m_texture = &texture; }
	const sf::Texture* getSpriteSheet() const { return m_texture; }
	std::size_t getSize() const { return m_frames.size(); }
	const sf::IntRect& getFrame(std::size_t n) const { return m_frames[n]; }
private:
	std::vector<sf::IntRect> m_frames;
	const sf::Texture* m_texture;
};
#endif