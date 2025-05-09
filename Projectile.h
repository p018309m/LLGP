#pragma once
#include <SFML/Graphics.hpp>
#include "ActorObject.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "HealthCaller.h"
#include "ScoreEvents.h"

class Projectile : public ActorObject
{
public:
	//Constructor
	Projectile();
	virtual ~Projectile();

	virtual void Fire(sf::Vector2f pos, sf::Vector2f dir);
	virtual bool isActive() { return active; }
	virtual void Deactivate();
	virtual int GetID() { return id; }
	virtual void SetID(int id) { this->id = id; }
	virtual void CollisionUpdate(CollisionManager& collisionManager);
	virtual void SetCollisionSize(float newSize) { collisionSizeMultiplier = newSize; }

	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(sf::RenderWindow& window) override;

	sf::Vector2f getVelocity() { return velocity; }
	virtual void setSpeed(float newSpeed) { projSpeed = newSpeed; }

	Collision* GetCollision() { return collisionComp; }

	virtual float GetLifeSpan() { return lifeSpan; }
	virtual void SetLifeSpan(float newLife) { lifeSpan = newLife; }

	virtual void SetOwner(ActorObject* owner) { this->owner = owner; }

	virtual void Handle_Death(ActorObject* objectHit, int val);

protected:
	bool active;

	ActorObject* owner;
	sf::CircleShape shape;
	float projSpeed = 0.005f;
	sf::Vector2f velocity;

	sf::RectangleShape body;

	float timer = 0.f;
	float lifeSpan;
	float collisionSizeMultiplier;

	Collision* collisionComp;
	int id;

};

