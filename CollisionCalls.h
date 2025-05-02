#pragma once
#include "Event.h"
#include "Collision.h"

namespace CollisionCall
{
	inline LLGP::Event<ColliderTag, int> OnPlayerCollided;
	inline LLGP::Event<ColliderTag, int> OnWorkersCollided;
	inline LLGP::Event<ColliderTag, int> OnWarriorsCollided;
	inline LLGP::Event<ColliderTag, int> OnProjectileCollided;
	inline LLGP::Event<ColliderTag, int> OnSinistarCollided;
	inline LLGP::Event<ColliderTag, int> OnCrystalCollided;
	inline LLGP::Event<ColliderTag, int> OnBombsCollided;
	inline LLGP::Event<ColliderTag, int> OnAsteroidCollided;
}