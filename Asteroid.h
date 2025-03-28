#pragma once

#include "SFML/Graphics.hpp"
#include "Collision.h"
class Asteroid
{
public:
	//Constructors and Destructors
	Asteroid();
	virtual ~Asteroid();

	//Functions
	void Draw(sf::RenderWindow& window);
	void Update();

	//Variables
	sf::Vector2f asteroidPos;
	sf::Angle asteroidDirection;
	sf::CircleShape body;

	//Texture
	const sf::Image asteroidImage = sf::Image("assets/sinistarsprites.jpg");
	sf::Texture asteroidText;
	bool result = asteroidText.loadFromImage(asteroidImage, false, sf::IntRect({ 242,90 }, { 24, 24 }));
	sf::Sprite asteroidSpritey = sf::Sprite(asteroidText);

	Collision GetCollision() { return Collision(body); }

private:
};

