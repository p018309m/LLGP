#pragma once
#include "ActorObject.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "HealthCaller.h"

class Crystal : public ActorObject
{
public:
	Crystal();
	virtual ~Crystal();

	void Begin() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window) override;
	void GetSent(sf::Vector2f position, sf::Vector2f direction);
	void SetLifeSpan(float newLife) { lifeSpan = newLife; }

	bool isActive() { return active; }
	void Activate(sf::Vector2f position);
	void Deactivate();
	int GetID() { return id; }
	void SetID(int id) { this->id = id; }

	void Handle_Death(ActorObject* objectHit, int health);

	Collision* GetCollision() { return collisionComp; }

protected:
	bool active;

private:
	sf::CircleShape shape;
	sf::RectangleShape body;

	Collision* collisionComp;
	int id;

	float timer = 0.f;
	float lifeSpan;
};

