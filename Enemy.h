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
	void Render(sf::RenderWindow& window) override;
	void Update(float deltaTime) override;
	void Activate(sf::Vector2f position);
	void Deactivate() { active = false; }

	//Variables
	sf::Vector2f enemyPos;
	sf::Angle enemyDirection;
	sf::RectangleShape body;

	Collision GetCollision() { return Collision(this, body); }

	bool isActive() { return active; }

private:

	Collision* collisionComp;
	bool active = false;
};

