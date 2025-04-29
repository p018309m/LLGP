#pragma once
#include <SFML/Graphics.hpp>
#include "ScoreEvents.h"
#include "ActorObject.h"

class Projectile : public ActorObject
{
public:
	//Constructor
	Projectile();
	virtual ~Projectile();

	virtual void Fire(sf::Vector2f pos, sf::Vector2f dir);
	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderWindow& window);
	virtual bool isActive() { return active; }
	virtual void Deactivate();
	sf::Vector2f getVelocity() { return velocity; }
	void setSpeed(float newSpeed) { projSpeed = newSpeed; }

protected:
	bool active;

private:
	sf::CircleShape shape;
	float projSpeed = 0.05f;
	sf::Vector2f velocity;

	float timer = 0.f;
	float lifeSpan = 1.f;

};

