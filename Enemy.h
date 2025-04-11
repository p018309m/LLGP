#pragma once
#include <SFML/Graphics.hpp>
#include "ActorObject.h"
#include "Collision.h"

class Enemy : public ActorObject
{
public:
	//Constructors and Destructors
	Enemy();
	virtual ~Enemy();

	//Functions
	void Draw(sf::RenderWindow& window);
	void Update();

	//Variables
	sf::Vector2f enemyPos;
	sf::Angle enemyDirection;
	sf::RectangleShape body;

	//Texture
	const sf::Image enemyImage = sf::Image("assets/enemy.png");
	sf::Texture enemyText;
	bool result = enemyText.loadFromImage(enemyImage, false, sf::IntRect({ 0,0 }, { 20, 20 }));
	sf::Sprite enemySpritey = sf::Sprite(enemyText);

	Collision GetCollision() { return Collision(this, body); }

private:
	Collision* collisionComp;
};

