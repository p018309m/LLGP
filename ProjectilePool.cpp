#include "ProjectilePool.h"
#include <iostream>

ProjectilePool::ProjectilePool(size_t poolSize)
{
	projectiles.resize(poolSize);
}

Projectile* ProjectilePool::getProjectiles()
{
	for(Projectile& proj : projectiles)
	{
		if (!proj.isActive())
			return &proj;
	}
	return nullptr;
}

void ProjectilePool::UpdateProjectiles(float deltaTime)
{
	for (Projectile& proj : projectiles)
	{
		proj.Update(deltaTime);
	}
}

void ProjectilePool::RenderProjectiles(sf::RenderWindow& window)
{
	for (Projectile& proj : projectiles)
	{
		proj.Render(window);
	}
}
