#include "ShootingComponent.h"
#include <iostream>

ShootingComponent::ShootingComponent(ActorObject* object, size_t poolSize, float fireRate) : Component(object), projPool(poolSize), fireRate(fireRate)
{
	
}

void ShootingComponent::Shoot(sf::Vector2f direction)
{
	if (!_object)
		return;

	std::cout << "fireTimer: " << fireTimer << ", fireRate: " << fireRate << std::endl;

	if (fireTimer < fireRate)
	{
		std::cout << "Cannot shoot yet. Waiting for cooldown.\n";
		return;
	}

	sf::Vector2f spawnPos = _object->getPosition();
	Projectile* proj = projPool.getProjectiles();

	if (proj)
	{
		fireTimer = 0.f;
		proj->Fire(spawnPos, direction);
	}
}

void ShootingComponent::Update(float deltaTime)
{
	fireTimer += deltaTime;
	projPool.UpdateProjectiles(deltaTime);
}

void ShootingComponent::Draw(sf::RenderWindow& window)
{
	projPool.RenderProjectiles(window);
}
