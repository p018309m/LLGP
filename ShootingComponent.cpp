#include "ShootingComponent.h"
#include <iostream>

ShootingComponent::ShootingComponent(ActorObject* object, size_t poolSize) : Component(object), projPool(poolSize)
{

}

void ShootingComponent::Shoot(sf::Vector2f direction)
{
	if (!_object)
		return;

	sf::Vector2f spawnPos = _object->getPosition();
	Projectile* proj = projPool.getProjectiles();

	if (proj)
		proj->Fire(spawnPos, direction);
}

void ShootingComponent::Update(float deltaTime)
{
	projPool.UpdateProjectiles(deltaTime);
}

void ShootingComponent::Draw(sf::RenderWindow& window)
{
	projPool.RenderProjectiles(window);
}
