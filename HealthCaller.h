#pragma once
#include "Event.h"
#include "ActorObject.h"

namespace HealthCall
{
	inline LLGP::Event<ActorObject*, int> OnDeath;
	inline LLGP::Event<int> OnDamageDealt;
	inline LLGP::Event<int> OnHeal;
	inline LLGP::Event<int> OnLivesChange;
}
