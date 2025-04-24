#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "StarPool.h"
#include <iostream>
#include "PlayerHUD.h"

//Main Game Handler
class Game
{
private:
	//Variables
	std::unique_ptr<sf::RenderWindow> window;
	sf::View hudWindow;

	Player mainPlayer;
	Input inputManager;
	Enemy enemy;
	Asteroid asteroid;
	StarPool starPool;
	sf::View view;
	PlayerHUD* playerHUD;
	sf::Font font;

	//Functions
	void InitialiseVariables();
	void InitialiseWindow();
	sf::Vector2f UpdateCameraMovement(float time, sf::View view, const Player& player);

	//Chrono Variables
	std::chrono::steady_clock::time_point lastTime;
	std::chrono::steady_clock::time_point currentTime;

	//Time Variables
	float deltaTime = 0.f;
	float physicsTimeStep = 20000.f;
	float tickLength = 10000.f;
	float timeSincePhysicsStep = 0.f;
	float timeSinceTick = 0.f;
	int totalTimeFixed = 0;
	int totalTimeTicked = 0;
	int totalTimeFree = 0;

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

