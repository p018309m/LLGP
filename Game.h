#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include <iostream>
//Main Game Handler
class Game
{
private:
	//Variables
	std::unique_ptr<sf::RenderWindow> window;
	Player mainPlayer;

	//Functions
	void InitialiseVariables();
	void InitialiseWindow();

public:
	//Constructors & Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool getGameRunning() const;

	//Functions
	void PollEvents();
	void Update();
	void Render();
};

