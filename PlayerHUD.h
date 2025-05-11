#pragma once
#include <SFML/Graphics.hpp>
#include "ScoreEvents.h"
#include "HealthCaller.h"

class PlayerHUD
{
public:
	PlayerHUD();
	~PlayerHUD();

	void SetHealth(int health);
	void SetBombCount(int bombs);
	void SetScore(int score);
	void Render(sf::RenderWindow& window);

private:
	sf::Text bombText = sf::Text(font, "", 18);
	sf::Text scoreText = sf::Text(font, "", 18);
	sf::Font font;

	std::vector<sf::Sprite> lifeIcons;
	sf::Texture shipTexture;
};

