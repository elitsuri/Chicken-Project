#pragma once
#include <vector>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include <random>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class Resources
{
public:
	Resources();
	~Resources() {};
	sf::Texture* getSpriteSheet(int index) { return m_SpriteSheets.at(index).get(); }
	Animation& getShipAnimation(int index){ return m_ShipAnimation.at(index); }
	Animation& getChickenAnimation(int index) { return m_chickenAnimation.at(index); }
	Animation& getBackgroundAnimation() { return m_backgroundAnimation; }
	Animation& getBulletsAnimations(int index) { return m_bulletsAnimations.at(index); }
	Animation& getBoomAnimation() { return m_boom; }
	Animation& getUpgradeAnimation() { return m_upgradeAnimation; }
	Animation& getGiftAnimation() { return m_giftAnimation; }
	Animation& getEggAnimation(int index) { return m_eggAnimation.at(index); }
	Animation& getBossAnimation() { return m_bossAnimation; }
	sf::Sound* getSound(int index) { return m_sounds.at(index).get(); }
	//random engine
	int RandomizeVal(float,float);
	void setPositionForCurser(sf::RenderWindow&win)const;
	sf::Sprite* getCurserAnimation()const { return m_curserAnimation.get(); }
	sf::Sprite* getMenuAnimation()const { return m_menuAnimation.get(); }
	sf::Text* getText(int index) { return m_texts.at(index).get(); }
private:
	std::vector<Animation> m_ShipAnimation;
	std::vector<Animation> m_chickenAnimation;
	std::vector<Animation> m_bulletsAnimations;
	std::vector<Animation> m_eggAnimation;
	Animation m_boom;
	Animation m_backgroundAnimation;
	Animation m_upgradeAnimation;
	Animation m_giftAnimation;
	Animation m_bossAnimation;
	std::vector<std::unique_ptr<sf::Texture>> m_SpriteSheets;
	std::vector<std::unique_ptr<sf::Text>> m_texts;
	std::vector<std::unique_ptr<sf::Sound>> m_sounds;
	std::vector<std::unique_ptr<sf::SoundBuffer>> m_soundSource;
	std::default_random_engine m_generator;
	std::unique_ptr<sf::Sprite> m_curserAnimation;
	std::unique_ptr<sf::Sprite> m_menuAnimation;
	std::unique_ptr<sf::Font> m_font;
};