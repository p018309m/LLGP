#include "EnemyManager.h"

EnemyManager::EnemyManager(int poolSize) : enemyPool(poolSize)
{
	int id = 0;
	for (auto& enemy : GetAllEnemies())
	{
		enemy->SetID(id);
		enemy->setSpeed(5.f);
		id++;
	}
}

void EnemyManager::Begin()
{
	for (auto& enemy : GetAllEnemies())
	{
		enemy->Begin();
		enemy->GetCollision()->SetActive(false);
	}
}

void EnemyManager::Update(float deltaTime)
{
	enemyPool.Update(deltaTime);
	timer += 0.01f;
	if (timer > maxTimer)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_real_distribution<float> dist(-2000.0f, 2000.0f);

		float x = dist(gen);
		float y = dist(gen);
		SpawnEnemy(sf::Vector2f(view.getCenter().x + x, view.getCenter().y + y));
		timer = 0.0f;
	}
}

void EnemyManager::CollisionUpdate(CollisionManager& collisionManager)
{
	for (auto& enemy : GetAllEnemies())
		if(enemy->isActive())
			enemy->CollisionUpdate(collisionManager);
}

void EnemyManager::PositionUpdate(sf::Vector2f pos)
{
	for (auto& enemy : GetAllEnemies())
		if (enemy->isActive())
			enemy->FollowPlayer(pos);
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
		enemy->GetCollision()->SetActive(true);
	}
}
