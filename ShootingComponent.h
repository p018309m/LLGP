#pragma once
#include "Component.h"
#include "ObjectPoolCommon.h"
#include "BombProjectile.h"
#include "Projectile.h"


class ShootingComponent : public Component
{
public:
	ShootingComponent(ActorObject* object, int projPoolSize, int bombPoolSize, float fireRate);

	void Shoot(sf::Vector2f direction);
	void Bomb(sf::Vector2f direction);
	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow& window);

private:
	ObjectPoolCommon<BombProjectile> bombPool;
	ObjectPoolCommon<Projectile> projPool;
	float fireRate;
	float fireTimer;
};

