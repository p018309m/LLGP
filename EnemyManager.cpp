#include "EnemyManager.h"

EnemyManager::EnemyManager(size_t poolSize) : enemyPool(poolSize)
{
}

void EnemyManager::Update(float deltaTime)
{
	enemyPool.Update(deltaTime);
}

void EnemyManager::Render(sf::RenderWindow& window)
{
	enemyPool.Render(window);
}

void EnemyManager::SpawnEnemy(sf::Vector2f position)
{
	Enemy* enemy = enemyPool.GetInactiveObjects();
	if (enemy)
		enemy->Activate(position);
}
