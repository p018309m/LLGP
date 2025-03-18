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

	LLGP::Event<int> OnMoveUp;
	void BroadcastOnMoveUp(int arg1);
	void HandleInput(std::optional<sf::Event> gameEvent, sf::RenderWindow& window);
};

