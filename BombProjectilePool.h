#pragma once
#include "BombProjectile.h"

class BombProjectilePool
{
public:
	BombProjectilePool(size_t poolSize);
	BombProjectile* getProjectiles();
	void UpdateProjectiles(float deltaTime);
	void RenderProjectiles(sf::RenderWindow& window);

private:
	std::vector<std::unique_ptr<BombProjectile>> projectiles;
};

