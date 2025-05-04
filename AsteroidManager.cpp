#include "AsteroidManager.h"

AsteroidManager::AsteroidManager(int poolSize) : asteroidPool(poolSize)
{
	int id = 0;
	for (auto& asteroid : GetAllAsteroids())
	{
		asteroid->SetID(id);
		asteroid->setSpeed(5.f);
		id++;
	}
}

void AsteroidManager::Begin()
{
}

void AsteroidManager::Update(float deltaTime)
{
}

void AsteroidManager::CollisionUpdate(CollisionManager& collisionManager)
{
}

void AsteroidManager::PositionUpdate(sf::Vector2f pos)
{
}

void AsteroidManager::Render(sf::RenderWindow& window)
{
}

void AsteroidManager::SpawnEnemy(sf::Vector2f position)
{
}
