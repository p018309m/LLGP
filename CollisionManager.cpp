#include "CollisionManager.h"

void CollisionManager::CheckCollisions(const std::function<void(Collision*, Collision*)>& onCollision)
{
	for (int i = 0; i < colliders.size(); ++i)
	{
		for (int j = i + 1; j < colliders.size(); ++j)
		{
			auto& a = colliders[i];
			auto& b = colliders[j];

			if (a && b && a->CheckCollision(*b))
				onCollision(a, b);
		}
	}
}
