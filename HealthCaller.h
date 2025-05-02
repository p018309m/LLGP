#pragma once
#include "Event.h"

namespace HealthCall
{
	inline LLGP::Event<int> OnDeath;
	inline LLGP::Event<int> OnDamageDealt;
	inline LLGP::Event<int> OnHeal;
	inline LLGP::Event<int> OnLivesChange;
}
