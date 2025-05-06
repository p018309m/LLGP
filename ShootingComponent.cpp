#include "ShootingComponent.h"
#include <iostream>

ShootingComponent::ShootingComponent(ActorObject* object, int projPoolSize, int bombPoolSize, float fireRate, float collisionSize) : Component(object), projPool(projPoolSize), bombPool(bombPoolSize), fireRate(fireRate), collisionSize(collisionSize)
{
	int idproj = 0;
	int idbomb = 0;

	for (auto& proj : GetAllProjectiles())
	{
		proj->SetID(idproj);
		idproj++;
		proj->SetLifeSpan(1.f);
		proj->SetCollisionSize(collisionSize);
		proj->Begin();
		proj->SetOwner(object);
	}

	for (auto& bomb : GetAllBombs())
	{
		bomb->SetID(idbomb);
		idbomb++;
		bomb->SetLifeSpan(100.f);
		bomb->Begin();
		bomb->SetOwner(object);
	}
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

void ShootingComponent::FixedUpdate(float deltaTime)
{
	for (auto& proj : GetAllProjectiles())
		proj->FixedUpdate(deltaTime);
	for (auto& bombs : GetAllBombs())
		bombs->FixedUpdate(deltaTime);
}

void ShootingComponent::CollisionUpdate(CollisionManager& collision)
{
	for (auto& proj : GetAllProjectiles())
		proj->CollisionUpdate(collision);
	for (auto& bombs : GetAllBombs())
		bombs->CollisionUpdate(collision);
}

void ShootingComponent::Draw(sf::RenderWindow& window)
{
	projPool.Render(window);
	bombPool.Render(window);
}
