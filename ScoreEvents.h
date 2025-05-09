#pragma once
#include "Event.h"


namespace ScorePoints
{
	inline LLGP::Event<int> OnEnemyDead;
	inline LLGP::Event<int> OnAddScore;
	inline LLGP::Event<int> OnScoreChange;
	inline LLGP::Event<int> FireRate;
}