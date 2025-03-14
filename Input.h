#pragma once
#include "Event.h"
class Input
{
public:
	LLGP::Event<int> OnMoveUp;
	void BroadcastOnMoveUp(int arg1);
};

