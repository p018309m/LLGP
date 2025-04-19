#pragma once
#include "Component.h"
#include "ProjectilePool.h"


class ShootingComponent : public Component
{
public:
	ShootingComponent(ActorObject* object, size_t poolSize);

	void Shoot(sf::Vector2f direction);
	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow& window);

private:
	ProjectilePool projPool;
};

