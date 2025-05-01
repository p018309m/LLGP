#pragma once
#include "Collision.h"
#include <functional>

class CollisionManager
{
public:
	void AddCollider(Collision* collider) { colliders.push_back(collider); }

	void Clear() { colliders.clear(); }

	void CheckCollisions(const std::function<void(Collision*, Collision*)>& onCollision);

private:
	std::vector<Collision*> colliders;
};

