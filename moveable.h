#pragma once

struct Player 
{
	float phealth = 100.f;
	float pspeed = .25f;
};

struct Enemy
{
	float ehealth = 25.f;
	float espeed = .05f;
};

class moveable
{
	void Move(float speed);
};

