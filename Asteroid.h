#pragma once

#include "SFML/Graphics.hpp"
#include "Collision.h"
class Asteroid : public ActorObject
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
	const sf::Image asteroidImage = sf::Image("assets/asteroid.png");
	sf::Texture asteroidText;
	bool result = asteroidText.loadFromImage(asteroidImage, false, sf::IntRect({ 0,0 }, { 52, 52 }));
	sf::Sprite asteroidSpritey = sf::Sprite(asteroidText);

	Collision GetCollision() { return Collision(this, body); }

private:
};

