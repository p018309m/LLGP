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

	void HandleInput(std::optional<sf::Event> gameEvent, sf::RenderWindow& window);

	//Event Keys
	LLGP::Event<sf::Keyboard::Key> OnMoveUp;
	LLGP::Event<sf::Keyboard::Key> OnMoveDown;
	LLGP::Event<sf::Keyboard::Key> OnMoveLeft;
	LLGP::Event<sf::Keyboard::Key> OnMoveRight;

	//Different Inputs
	void BroadcastOnMoveUp(sf::Keyboard::Key key);
	void BroadcastOnMoveDown(sf::Keyboard::Key key);
	void BroadcastOnMoveLeft(sf::Keyboard::Key key);
	void BroadcastOnMoveRight(sf::Keyboard::Key key);
};

