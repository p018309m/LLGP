#include "EnemyManager.h"

EnemyManager::EnemyManager(int poolSize) : enemyPool(poolSize)
{
	int id = 0;
	for (auto& enemy : GetAllEnemies())
	{
		enemy->SetID(id);
		id++;
	}
}

void EnemyManager::Begin()
{
	for (auto& enemy : GetAllEnemies())
		enemy->Begin();
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
	{
		enemy->Activate(position);
	}
}
