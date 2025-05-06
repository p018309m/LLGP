#pragma once
#include "SFML/Graphics.hpp"
#include "ObjectPoolCommon.h"
#include "Enemy.h"
#include <random>

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

	std::vector<std::unique_ptr<Enemy>>& GetAllEnemies() { return enemyPool.GetAllObjects(); }

	void SetView(sf::View view) { this->view = view; }

private:
	ObjectPoolCommon<Enemy> enemyPool;

	float timer = 0.f;
	float maxTimer = 1.f;

	sf::View view;
};

