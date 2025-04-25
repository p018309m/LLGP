#include "BombProjectilePool.h"

BombProjectilePool::BombProjectilePool(size_t poolSize)
{
	projectiles.reserve(poolSize);

	for (size_t i = 0; i < poolSize; ++i) {
		projectiles.push_back(std::make_unique<BombProjectile>());
	}
}

BombProjectile* BombProjectilePool::getProjectiles()
{
	for (auto& proj : projectiles)
	{
		if (!proj->isActive())
			return proj.get();
	}
	return nullptr;
}

void BombProjectilePool::UpdateProjectiles(float deltaTime)
{
	for (auto& proj : projectiles)
	{
		proj->Update(deltaTime);
	}
}

void BombProjectilePool::RenderProjectiles(sf::RenderWindow& window)
{
	for (auto& proj : projectiles)
	{
		proj->Render(window);
	}
}
