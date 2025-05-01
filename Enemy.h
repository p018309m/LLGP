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
	void Begin() override;
	void Render(sf::RenderWindow& window) override;
	void Update(float deltaTime) override;
	void Activate(sf::Vector2f position);
	void Deactivate() { active = false; }

	//Variables
	sf::Vector2f enemyPos;
	sf::Angle enemyDirection;
	sf::RectangleShape body;

	int GetID() const { return id; }
	void SetID(int id) { this->id = id; }

	Collision* GetCollision() { return collisionComp; }

	bool isActive() { return active; }

private:
	int id = -1;
	Collision* collisionComp;
	bool active = false;
};

