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
	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime) override;
	void CollisionUpdate(CollisionManager& collision);

	std::vector<std::unique_ptr<Projectile>>& GetAllProjectiles() { return projPool.GetAllObjects(); }
	std::vector<std::unique_ptr<BombProjectile>>& GetAllBombs() { return bombPool.GetAllObjects(); }

private:
	ObjectPoolCommon<BombProjectile> bombPool;
	ObjectPoolCommon<Projectile> projPool;

	float fireRate;
	float fireTimer;
};

