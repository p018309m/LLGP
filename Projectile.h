#pragma once
#include <SFML/Graphics.hpp>
#include "ScoreEvents.h"
#include "ActorObject.h"
#include "Collision.h"

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

	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(sf::RenderWindow& window) override;

	sf::Vector2f getVelocity() { return velocity; }
	void setSpeed(float newSpeed) { projSpeed = newSpeed; }

	Collision* GetCollision() { return collisionComp; }

protected:
	bool active;

private:
	sf::CircleShape shape;
	float projSpeed = 0.005f;
	sf::Vector2f velocity;

	sf::RectangleShape body;

	float timer = 0.f;
	float lifeSpan = 1.f;

	Collision* collisionComp;
	int id;

};

