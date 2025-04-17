#pragma once
#include "Event.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Input
{
public:
	//Constructors and Destructors
	Input();
	virtual ~Input();

	void HandleInput();

	//Event Keys
	LLGP::Event<int> OnMoveUp;
	LLGP::Event<int> OnMoveDown;
	LLGP::Event<int> OnMoveLeft;
	LLGP::Event<int> OnMoveRight;
	LLGP::Event<int> OnShoot;

	//Different Inputs
	void BroadcastOnMoveUp(int val);
	void BroadcastOnMoveDown(int val);
	void BroadcastOnMoveLeft(int val);
	void BroadcastOnMoveRight(int val);
	void BroadcastOnShoot(int val);
};

