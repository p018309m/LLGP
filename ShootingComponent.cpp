#include "ShootingComponent.h"
#include <iostream>

ShootingComponent::ShootingComponent(ActorObject* object, size_t poolSize, float fireRate) : Component(object), projPool(poolSize), fireRate(fireRate)
{
	
}

void ShootingComponent::Shoot(sf::Vector2f direction)
{
	if (!_object)
		return;

	if (fireTimer < fireRate)
		return;

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
	fireTimer += 0.01f;
	projPool.UpdateProjectiles(deltaTime);
}

void ShootingComponent::Draw(sf::RenderWindow& window)
{
	projPool.RenderProjectiles(window);
}
