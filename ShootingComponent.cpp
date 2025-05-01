#include "ShootingComponent.h"
#include <iostream>

ShootingComponent::ShootingComponent(ActorObject* object, int projPoolSize, int bombPoolSize, float fireRate) : Component(object), projPool(projPoolSize), bombPool(bombPoolSize), fireRate(fireRate)
{
	
}

void ShootingComponent::Shoot(sf::Vector2f direction)
{
	if (!_object)
		return;

	if (fireTimer < fireRate)
		return;

	sf::Vector2f spawnPos = _object->getPosition();
	Projectile* proj = projPool.GetInactiveObjects();


	if (proj)
	{
		fireTimer = 0.f;
		proj->Fire(spawnPos, direction);
	}
}

void ShootingComponent::Bomb(sf::Vector2f direction)
{
	if (!_object)
		return;

	if (fireTimer < fireRate)
		return;

	sf::Vector2f spawnPos = _object->getPosition();

	BombProjectile* bomb = bombPool.GetInactiveObjects();
	if (bomb)
	{
		fireTimer = 0.f;
		bomb->Fire(spawnPos, direction);
	}
}

void ShootingComponent::Update(float deltaTime)
{
	fireTimer += 0.01f;
	projPool.Update(deltaTime);
	bombPool.Update(deltaTime);
}

void ShootingComponent::Draw(sf::RenderWindow& window)
{
	projPool.Render(window);
	bombPool.Render(window);
}
