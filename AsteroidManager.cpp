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
	for (auto& asteroid : GetAllAsteroids())
		asteroid->Begin();
}

void AsteroidManager::Update(float deltaTime)
{
	asteroidPool.Update(deltaTime);
}

void AsteroidManager::CollisionUpdate(CollisionManager& collisionManager)
{
	for (auto& asteroid : GetAllAsteroids())
		if (asteroid->isActive())
			asteroid->CollisionUpdate(collisionManager);
}

void AsteroidManager::PositionUpdate(sf::Vector2f pos)
{
	for (auto& asteroid : GetAllAsteroids())
		if (asteroid->isActive())
			asteroid->MoveAsteroid();
}

void AsteroidManager::Render(sf::RenderWindow& window)
{
	asteroidPool.Render(window);
}

void AsteroidManager::SpawnAsteroid(sf::Vector2f position)
{
	Asteroid* asteroid = asteroidPool.GetInactiveObjects();
	if (asteroid)
		asteroid->Activate(position);
}
