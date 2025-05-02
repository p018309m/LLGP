#pragma once
#include "Collision.h"
#include <functional>

class CollisionManager
{
public:
	void AddCollider(Collision* collider) { colliders.push_back(collider); }

	void Clear() { colliders.clear(); }

	std::vector<Collision*> GetAllColliders() { return colliders; }

private:
	std::vector<Collision*> colliders;
};

