#pragma once
#include "SFML/Graphics.hpp"
#include "Collision.h"
#include "HealthComponent.h"
#include "ScoreEvents.h"
#include "CollisionManager.h"

class Asteroid : public ActorObject
{
public:
	//Constructors and Destructors
	Asteroid();
	virtual ~Asteroid();

	//Functions
	void Begin() override;
	void Render(sf::RenderWindow& window) override;
	void Update(float deltaTime) override;
	void CollisionUpdate(CollisionManager& collisionManager);
	void Activate(sf::Vector2f position);
	void Deactivate() { active = false; }

	//Variables
	sf::Vector2f asteroidPos;
	sf::Angle asteroidDirection;
	sf::RectangleShape body;
	
	int GetID() const { return id; }
	void SetID(int id) { this->id = id; }

	void MoveAsteroid();

	Collision* GetCollision() { return collisionComp; }

	bool isActive() { return active; }

	void Handle_Death(ActorObject* objectHit, int val);

private:
	int id = -1;
	Collision* collisionComp;
	HealthComponent* healthComp;
	bool active = false;
	float actualSpeed;
};

