#pragma once
#include "SFML/Graphics.hpp"
#include "ObjectPoolCommon.h"
#include "Asteroid.h"
#include <random>

class AsteroidManager
{
public:
	AsteroidManager(int poolSize);

	void Begin();
	void Update(float deltaTime);
	void CollisionUpdate(CollisionManager& collisionManager);
	void PositionUpdate(sf::Vector2f pos);
	void Render(sf::RenderWindow& window);

	void SpawnAsteroid(sf::Vector2f position);

	std::vector<std::unique_ptr<Asteroid>>& GetAllAsteroids() { return asteroidPool.GetAllObjects(); }

private:
	ObjectPoolCommon<Asteroid> asteroidPool;

	float timer = 0.f;
	float maxTimer = 1.f;

	sf::Vector2f playerPos;
};

