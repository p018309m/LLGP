#include "EnemyManager.h"

EnemyManager::EnemyManager(int poolSize) : enemyPool(poolSize), warriorPool(poolSize)
{
	int id = 0;
	int idW = 0;
	for (auto& enemy : GetAllEnemies())
	{
		enemy->SetID(id);
		enemy->setSpeed(5.f);
		id++;
	}
	for (auto& warrior : GetAllWarriors())
	{
		warrior->SetID(idW);
		warrior->setSpeed(3.f);
		idW++;
	}
}

void EnemyManager::Begin()
{
	for (auto& enemy : GetAllEnemies())
	{
		enemy->Begin();
		enemy->GetCollision()->SetActive(false);
	}
	for (auto& warrior : GetAllWarriors())
	{
		warrior->Begin();
		warrior->GetCollision()->SetActive(false);
	}
}

void EnemyManager::Update(float deltaTime)
{
	timer += 0.01f;
	if (timer > maxTimer)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_real_distribution<float> dist(-500.0f, 500.0f);

		float x = dist(gen);
		float y = dist(gen);
		SpawnEnemy(sf::Vector2f(playerPos.x + x, playerPos.y + y));
		SpawnWarrior(sf::Vector2f(playerPos.x - x, playerPos.y - y));
		timer = 0.0f;
	}
	warriorPool.Update(deltaTime);
	enemyPool.Update(deltaTime);
}

void EnemyManager::CollisionUpdate(CollisionManager& collisionManager)
{
	for (auto& enemy : GetAllEnemies())
		if(enemy->isActive())
			enemy->CollisionUpdate(collisionManager);
	for (auto& warrior : GetAllWarriors())
		if (warrior->isActive())
			warrior->CollisionUpdate(collisionManager);
}

void EnemyManager::PositionUpdate(sf::Vector2f pos)
{
	playerPos = pos;
	for (auto& enemy : GetAllEnemies())
		if (enemy->isActive())
			enemy->FollowPlayer(pos);
	for (auto& warrior : GetAllWarriors())
		if (warrior->isActive())
			warrior->FollowPlayer(pos);
}

void EnemyManager::Render(sf::RenderWindow& window)
{
	enemyPool.Render(window);
	warriorPool.Render(window);
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

void EnemyManager::SpawnWarrior(sf::Vector2f position)
{
	Warriors* warriors = warriorPool.GetInactiveObjects();
	if (warriors)
	{
		warriors->Activate(position);
		warriors->GetCollision()->SetActive(true);
	}
}
