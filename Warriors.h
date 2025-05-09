#pragma once
#include "Enemy.h"
#include "ShootingComponent.h"

template<typename T>
bool NearlyEqualAngle(T a, T b, T diff = static_cast<T>(1.f))
{
	return std::abs(a - b) < diff;
}

class Warriors : public Enemy
{
public:

	Warriors();
	virtual ~Warriors();

	void Begin() override;
	void Render(sf::RenderWindow& window) override;
	void FollowPlayer(sf::Vector2f& playerPos) override;
	void ShootPlayer(sf::Vector2f playerLoc);
	void Update(float deltaTime) override;
	void CollisionUpdate(CollisionManager& collisionManager) override;

	void Handle_Death(ActorObject* objectHit, int val) override;

	void Activate(sf::Vector2f position) override;
	void Deactivate() override { active = false; }

	bool isActive() override { return active; }

	Collision* GetCollision() { return collisionComp; }
	ShootingComponent* GetShootComp() { return shootComp; }

private:
	int id = -1;
	Collision* collisionComp;
	HealthComponent* healthComp;
	ShootingComponent* shootComp;
	bool active = false;
	float actualSpeed;
};

