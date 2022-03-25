#include "Resources.h"
#include <random>
#include <SFML/Window/Mouse.hpp>
#include <chrono>
#include "FileNotOpenEx.h"

Resources::Resources()
{
	int seed = std::chrono::steady_clock::now().time_since_epoch().count();
	m_generator.seed(seed);
	m_sounds.push_back(std::make_unique<sf::Sound>());
	m_soundSource.push_back(std::make_unique<sf::SoundBuffer>());
	if (!m_soundSource[0]->loadFromFile("Ionblaster.ogx"))
		throw FileNotOpenEx();
	m_sounds[0]->setBuffer(*m_soundSource[0]);
	m_sounds[0]->setVolume(10);
	m_sounds.push_back(std::make_unique<sf::Sound>());
	m_soundSource.push_back(std::make_unique<sf::SoundBuffer>());
	if (!m_soundSource[1]->loadFromFile("packpack.oga"))
		throw FileNotOpenEx();
	m_sounds[1]->setBuffer(*m_soundSource[1]);
	m_sounds[1]->setVolume(100);
	m_sounds.push_back(std::make_unique<sf::Sound>());
	m_soundSource.push_back(std::make_unique<sf::SoundBuffer>());
	if (!m_soundSource[2]->loadFromFile("layEgg.oga"))
		throw FileNotOpenEx();
	m_sounds[2]->setBuffer(*m_soundSource[2]);
	m_sounds[2]->setVolume(50);
	m_sounds.push_back(std::make_unique<sf::Sound>());
	m_soundSource.push_back(std::make_unique<sf::SoundBuffer>());
	if (!m_soundSource[3]->loadFromFile("eggOnGround.oga"))
		throw FileNotOpenEx();
	m_sounds[3]->setBuffer(*m_soundSource[3]);
	m_sounds[3]->setVolume(50);
	m_sounds.push_back(std::make_unique<sf::Sound>());
	m_soundSource.push_back(std::make_unique<sf::SoundBuffer>());
	if (!m_soundSource[4]->loadFromFile("menuSound.oga"))
		throw FileNotOpenEx();
	m_sounds[4]->setBuffer(*m_soundSource[4]);
	m_sounds[4]->setVolume(100);
	m_sounds.push_back(std::make_unique<sf::Sound>());
	m_soundSource.push_back(std::make_unique<sf::SoundBuffer>());
	if (!m_soundSource[5]->loadFromFile("gameover.oga"))
		throw FileNotOpenEx();
	m_sounds[5]->setBuffer(*m_soundSource[5]);
	m_sounds[5]->setVolume(100);
	m_sounds.push_back(std::make_unique<sf::Sound>());
	m_soundSource.push_back(std::make_unique<sf::SoundBuffer>());
	if (!m_soundSource[6]->loadFromFile("playerhit.oga"))
		throw FileNotOpenEx();
	m_sounds[6]->setBuffer(*m_soundSource[6]);
	m_sounds[6]->setVolume(100);
	m_sounds.push_back(std::make_unique<sf::Sound>());
	m_soundSource.push_back(std::make_unique<sf::SoundBuffer>());
	if (!	m_soundSource[7]->loadFromFile("BossHit.oga"))
		throw FileNotOpenEx();
	m_sounds[7]->setBuffer(*m_soundSource[7]);
	m_sounds[7]->setVolume(100);
	m_sounds.push_back(std::make_unique<sf::Sound>());
	m_soundSource.push_back(std::make_unique<sf::SoundBuffer>());
	if (!m_soundSource[8]->loadFromFile("BossDie.oga"))
		throw FileNotOpenEx();
	m_sounds[8]->setBuffer(*m_soundSource[8]);
	m_sounds[8]->setVolume(100);
    m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>() );
	if (!m_SpriteSheets[0]->loadFromFile("ship.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[1]->loadFromFile("chickenSpriteSheet.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[2]->loadFromFile("spaceBalck.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[3]->loadFromFile("fireSmall.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[4]->loadFromFile("boom.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[5]->loadFromFile("eggspritesheet.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[6]->loadFromFile("fork1.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[7]->loadFromFile("menuwithlogonobuttons.jpg"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[8]->loadFromFile("fork2.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[9]->loadFromFile("upgrade.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[10]->loadFromFile("gift.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[11]->loadFromFile("shipExplosion.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[12]->loadFromFile("boss.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[13]->loadFromFile("gameover.png"))
		throw FileNotOpenEx();
	m_SpriteSheets.emplace_back(std::make_unique<sf::Texture>());
	if (!m_SpriteSheets[14]->loadFromFile("win.png"))
		throw FileNotOpenEx();
	m_ShipAnimation.emplace_back(Animation());
	m_ShipAnimation[0].setSpriteSheet(*m_SpriteSheets[0]);
	m_ShipAnimation[0].addFrame(sf::IntRect(0, 0, 38, 84));
	m_ShipAnimation.emplace_back(Animation());
	m_ShipAnimation[1].setSpriteSheet(*m_SpriteSheets[0]);
	m_ShipAnimation[1].addFrame(sf::IntRect(0, 0, 38, 45));
	m_ShipAnimation.emplace_back(Animation());
	m_ShipAnimation[2].setSpriteSheet(*m_SpriteSheets[0]);
	m_ShipAnimation[2].addFrame(sf::IntRect(41, 0, 38, 45));
	m_ShipAnimation[2].addFrame(sf::IntRect(82, 0, 38, 45));
	m_ShipAnimation.emplace_back(Animation());
	m_ShipAnimation[3].setSpriteSheet(*m_SpriteSheets[0]);
	m_ShipAnimation[3].addFrame(sf::IntRect(123, 0, 38, 45));
	m_ShipAnimation[3].addFrame(sf::IntRect(164, 0, 38, 45));
	m_ShipAnimation.emplace_back(Animation());
	m_ShipAnimation[4].setSpriteSheet(*m_SpriteSheets[11]);
	m_ShipAnimation[4].addFrame(sf::IntRect(162, 39, 86, 89));
	m_ShipAnimation[4].addFrame(sf::IntRect(280, 32, 86, 89));
	m_ShipAnimation[4].addFrame(sf::IntRect(411, 26, 86, 89));
	m_ShipAnimation[4].addFrame(sf::IntRect(522, 28, 86, 89));
	m_ShipAnimation[4].addFrame(sf::IntRect(668, 39, 86, 89));
	m_ShipAnimation[4].addFrame(sf::IntRect(802, 24, 86, 89));
	m_ShipAnimation[4].addFrame(sf::IntRect(922, 22, 86, 89));
	m_ShipAnimation[4].addFrame(sf::IntRect(1054, 21, 86, 89));
	m_ShipAnimation[4].addFrame(sf::IntRect(1178, 21, 86, 89));
	m_bulletsAnimations.emplace_back(Animation{});
	m_bulletsAnimations[0].setSpriteSheet(*m_SpriteSheets[3]);
	m_bulletsAnimations[0].addFrame(sf::IntRect(0, 0, 15, 30));
	m_bulletsAnimations.emplace_back(Animation{});
	m_bulletsAnimations[1].setSpriteSheet(*m_SpriteSheets[3]);
	m_bulletsAnimations[1].addFrame(sf::IntRect(0, 0, 30, 30));
	m_bulletsAnimations.emplace_back(Animation{});
	m_bulletsAnimations[2].setSpriteSheet(*m_SpriteSheets[3]);
	m_bulletsAnimations[2].addFrame(sf::IntRect(0, 0, 45, 30));
	m_chickenAnimation.resize(4);
	for (auto& element : m_chickenAnimation)
	{
			element.setSpriteSheet(*m_SpriteSheets[1]);
		for (int i = 0; i < 4; ++i)
			element.addFrame(sf::IntRect(i*100, 0, 100, 85));

		for (int i = 3; i >= 0; --i)
			element.addFrame(sf::IntRect(i*100, 0, 100, 85));
	}
	m_boom.setSpriteSheet(*m_SpriteSheets[4]);
	m_boom.addFrame(sf::IntRect(0, 0, 127.5, 110));
	m_boom.addFrame(sf::IntRect(127.5, 0, 127.5, 110));
	m_boom.addFrame(sf::IntRect(255, 0, 127.5, 110));
	m_boom.addFrame(sf::IntRect(382.5, 0, 127.5, 110));
	m_boom.addFrame(sf::IntRect(0, 113, 128, 110));
	m_boom.addFrame(sf::IntRect(128, 113, 128, 110));
	m_boom.addFrame(sf::IntRect(256, 113, 128, 110));
	m_boom.addFrame(sf::IntRect(384, 113, 128, 110));
	m_boom.addFrame(sf::IntRect(0, 259, 127.5, 113));
	m_boom.addFrame(sf::IntRect(127.5, 259, 127.5, 113));
	m_boom.addFrame(sf::IntRect(255, 259, 127.5, 113));
	m_boom.addFrame(sf::IntRect(382.5, 259, 127.5, 113));
	m_boom.addFrame(sf::IntRect(0, 383, 127.5, 110));
	m_boom.addFrame(sf::IntRect(127.5, 383, 127.5, 110));
	m_boom.addFrame(sf::IntRect(255, 383, 127.5, 110));
	m_boom.addFrame(sf::IntRect(382.5, 383, 127.5, 110));
	m_backgroundAnimation.setSpriteSheet(*m_SpriteSheets[2]);
	for (int i = 650; i >= 0; --i)
		m_backgroundAnimation.addFrame(sf::IntRect(230, i , 1920, 1080));
	m_eggAnimation.emplace_back(Animation{});
	m_eggAnimation[0].setSpriteSheet(*m_SpriteSheets[5]);
	m_eggAnimation[0].addFrame(sf::IntRect(0, 0, 25, 31));
	m_eggAnimation.emplace_back(Animation{});
	m_eggAnimation[1].setSpriteSheet(*m_SpriteSheets[5]);
	m_eggAnimation[1].addFrame(sf::IntRect(28, 0, 56, 31));
	m_upgradeAnimation.setSpriteSheet(*m_SpriteSheets[9]);
	m_upgradeAnimation.addFrame(sf::IntRect( 0, 0, 46, 32 ));
	m_giftAnimation.setSpriteSheet(*m_SpriteSheets[10]);
	m_giftAnimation.addFrame(sf::IntRect(0, 0, 42, 31));
	m_bossAnimation.setSpriteSheet(*m_SpriteSheets[12]);
	m_bossAnimation.addFrame(sf::IntRect(0, 0, 300, 270));
	m_curserAnimation = std::make_unique<sf::Sprite>();
	m_curserAnimation->setTexture(*m_SpriteSheets[6]);
	m_menuAnimation = std::make_unique<sf::Sprite>();
	m_menuAnimation->setTexture(*m_SpriteSheets[7]);
	m_font = std::make_unique<sf::Font>();
	m_font->loadFromFile("Future TimeSplitters.otf");
	m_texts.emplace_back(std::make_unique<sf::Text>());
	m_texts[0]->setFont(*m_font);
	m_texts[0]->setCharacterSize(160);
	m_texts[0]->setFillColor(sf::Color(128, 192, 253));
	m_texts.emplace_back(std::make_unique<sf::Text>());
	m_texts[1]->setFont(*m_font);
	m_texts[1]->setCharacterSize(160);
	m_texts[1]->setFillColor(sf::Color(128, 192, 253));
	m_texts.emplace_back(std::make_unique<sf::Text>());
	m_texts[2]->setFont(*m_font);
	m_texts[2]->setCharacterSize(160);
	m_texts[2]->setFillColor(sf::Color(128, 192, 253));
	m_texts.emplace_back(std::make_unique<sf::Text>());
	m_texts[3]->setFont(*m_font);
	m_texts[3]->setCharacterSize(45);
	m_texts[3]->setFillColor(sf::Color(128, 192, 253));
	m_texts.emplace_back(std::make_unique<sf::Text>());
	m_texts[4]->setFont(*m_font);
	m_texts[4]->setCharacterSize(45);
	m_texts[4]->setFillColor(sf::Color(128, 192, 253));
}

int Resources::RandomizeVal(float m_leftBand,float m_rightBand)
{
	
	std::uniform_int_distribution<> distribution(m_leftBand, m_rightBand);
	
	int dice_roll = distribution(m_generator);
	return dice_roll;
}

void Resources::setPositionForCurser(sf::RenderWindow& win)const
{
	m_curserAnimation->setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(win)));
	sf::View fixed = win.getView();
	win.setView(fixed);
}