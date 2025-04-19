#pragma once
#include "Projectile.h"

class ProjectilePool
{
public:
	ProjectilePool(size_t poolSize);
	Projectile* getProjectiles();
	void UpdateProjectiles(float deltaTime);
	void RenderProjectiles(sf::RenderWindow& window);

private:
	std::vector<Projectile> projectiles;
};

