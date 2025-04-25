#pragma once
#include "Component.h"
#include "ProjectilePool.h"
#include "BombProjectilePool.h"


class ShootingComponent : public Component
{
public:
	ShootingComponent(ActorObject* object, size_t poolSize, float fireRate);

	void Shoot(sf::Vector2f direction);
	void Bomb(sf::Vector2f direction);
	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow& window);

private:
	ProjectilePool projPool;
	BombProjectilePool bombPool;
	float fireRate;
	float fireTimer;
};

