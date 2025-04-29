#pragma once
#include "SFML/Graphics.hpp"
#include "ObjectPoolCommon.h"
#include "Enemy.h"

class EnemyManager
{
public:
	EnemyManager(size_t poolSize);

	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);

	void SpawnEnemy(sf::Vector2f position);

private:
	ObjectPoolCommon<Enemy> enemyPool;
};

