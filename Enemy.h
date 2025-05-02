#pragma once
#include <SFML/Graphics.hpp>
#include "ActorObject.h"
#include "Collision.h"
#include "HealthComponent.h"
#include "CollisionManager.h"

class Enemy : public ActorObject
{
public:
	//Constructors and Destructors
	Enemy();
	virtual ~Enemy();

	//Functions
	virtual void Begin() override;
	virtual void Render(sf::RenderWindow& window) override;
	virtual void Update(float deltaTime) override;
	virtual void CollisionUpdate(CollisionManager& collisionManager);
	virtual void Activate(sf::Vector2f position);
	virtual void Deactivate() { active = false; }

	//Variables
	sf::Vector2f enemyPos;
	sf::Angle enemyDirection;
	sf::RectangleShape body;

	virtual int GetID() const { return id; }
	virtual void SetID(int id) { this->id = id; }

	Collision* GetCollision() { return collisionComp; }

	virtual bool isActive() { return active; }

	virtual void Handle_Death(int val);

private:
	int id = -1;
	Collision* collisionComp;
	HealthComponent* healthComp;
	bool active = false;
};

