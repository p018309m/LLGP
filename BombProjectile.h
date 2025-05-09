#pragma once
#include "Projectile.h"
#include "AnimationComponent.h"

class BombProjectile : public Projectile
{
public:
	BombProjectile();

	void Begin() override;
	void Fire(sf::Vector2f pos, sf::Vector2f dir) override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window) override;
	void CollisionUpdate(CollisionManager& collisionManager);
	bool isActive() override { return active; }
	void Deactivate();

private:
	AnimationComponent* animComp;

	float timer;
};

