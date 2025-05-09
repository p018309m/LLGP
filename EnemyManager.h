#pragma once
#include "SFML/Graphics.hpp"
#include "ObjectPoolCommon.h"
#include "Enemy.h"
#include <random>
#include "Warriors.h"

class EnemyManager
{
public:
	EnemyManager(int poolSize);

	void Begin();
	void Update(float deltaTime);
	void CollisionUpdate(CollisionManager& collisionManager);
	void PositionUpdate(sf::Vector2f pos);
	void Render(sf::RenderWindow& window);

	void SpawnEnemy(sf::Vector2f position);
	void SpawnWarrior(sf::Vector2f position);

	std::vector<std::unique_ptr<Enemy>>& GetAllEnemies() { return enemyPool.GetAllObjects(); }
	std::vector<std::unique_ptr<Warriors>>& GetAllWarriors() { return warriorPool.GetAllObjects(); }

private:
	ObjectPoolCommon<Enemy> enemyPool;
	ObjectPoolCommon<Warriors> warriorPool;

	float timer = 0.f;
	float maxTimer = 1.f;

	sf::Vector2f playerPos;
};

