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
	void Render(sf::RenderWindow& window);
	void Update();

	//Variables
	sf::Vector2f enemyPos;
	sf::Angle enemyDirection;
	sf::RectangleShape body;

	Collision GetCollision() { return Collision(this, body); }

private:
	Collision* collisionComp;
};

