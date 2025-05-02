#pragma once
#include "SFML/Graphics.hpp"
#include "ObjectPoolCommon.h"
#include "Enemy.h"

class EnemyManager
{
public:
	EnemyManager(int poolSize);

	void Begin();
	void Update(float deltaTime);
	void CollisionUpdate(CollisionManager& collisionManager);
	void Render(sf::RenderWindow& window);

	void SpawnEnemy(sf::Vector2f position);

	std::vector<std::unique_ptr<Enemy>>& GetAllEnemies() { return enemyPool.GetAllObjects(); }

private:
	ObjectPoolCommon<Enemy> enemyPool;
};

