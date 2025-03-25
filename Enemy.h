#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"

class Enemy
{
public:
	//Constructors and Destructors
	Enemy();
	virtual ~Enemy();

	//Functions
	void Draw(sf::RenderWindow& window);
	void Update(std::optional<sf::Event> gameEvent, sf::RenderWindow& window);

	//Variables
	sf::Vector2f enemyPos;
	sf::Angle enemyDirection;
	sf::RectangleShape body;
	sf::RectangleShape ref;

	//Texture
	const sf::Image enemyImage = sf::Image("assets/sinistarsprites.jpg");
	sf::Texture enemyText;
	bool result = enemyText.loadFromImage(enemyImage, false, sf::IntRect({ 242,90 }, { 24, 24 }));
	sf::Sprite enemySpritey = sf::Sprite(enemyText);

	Collision GetCollision() { return Collision(body); }

private:
};

