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
	{
		asteroid->Begin();
		asteroid->GetCollision()->SetActive(false);
		asteroid->setSpeed(1.f);
		asteroid->SetVelocity();
	}
}

void AsteroidManager::Update(float deltaTime)
{
	timer += 0.01f;
	if (timer > maxTimer)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_real_distribution<float> dist(-500.0f, 500.0f);

		float x = dist(gen);
		float y = dist(gen);
		SpawnAsteroid(sf::Vector2f(playerPos.x + x, playerPos.y + y));
		timer = 0.0f;
	}
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
	playerPos = pos;
	for (auto& asteroid : GetAllAsteroids())
		if (asteroid->isActive())
			asteroid->MoveAsteroid(pos);
}

void AsteroidManager::Render(sf::RenderWindow& window)
{
	asteroidPool.Render(window);
}

void AsteroidManager::SpawnAsteroid(sf::Vector2f position)
{
	Asteroid* asteroid = asteroidPool.GetInactiveObjects();
	if (asteroid)
	{
		asteroid->Activate(position);
		asteroid->GetCollision()->SetActive(true);
	}
}
