#include "ProjectilePool.h"

ProjectilePool::ProjectilePool(size_t poolSize)
{
	projectiles.resize(poolSize);
}

Projectile* ProjectilePool::getProjectiles()
{
	for(auto& proj : projectiles)
	{
		if (!proj.isActive())
			return &proj;
	}
	return nullptr;
}

void ProjectilePool::UpdateProjectiles(float deltaTime)
{
	for (auto& proj : projectiles)
	{
		proj.Update(deltaTime);
	}
}

void ProjectilePool::RenderProjectiles(sf::RenderWindow& window)
{
	for (auto& proj : projectiles)
	{
		proj.Render(window);
	}
}
