#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "StarPool.h"
#include <iostream>
#include "PlayerHUD.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "CollisionCalls.h"
#include "Crystal.h"
#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 640

//Main Game Handler
class Game
{
private:
	//Variables

	//Views and Windows
	std::unique_ptr<sf::RenderWindow> window;
	sf::View view;
	sf::View minimapView;
	sf::View hudView;

	//Classes
	std::unique_ptr<Player> mainPlayer;
	Input inputManager;
	std::unique_ptr<Asteroid> asteroid;
	std::unique_ptr<StarPool> starPool;
	std::unique_ptr<EnemyManager> enemyManager;
	std::unique_ptr<PlayerHUD> playerHUD;
	sf::Font font;

	std::unique_ptr<CollisionManager> collisionManager;

	sf::Image borderImage = sf::Image("assets/border.png");
	sf::Texture borderTexture;
	bool result = borderTexture.loadFromImage(borderImage, false, sf::IntRect({ 0,0 }, { 78, 69 }));
	sf::Sprite borderSprite = sf::Sprite(borderTexture);
	sf::RectangleShape divider;
	sf::RectangleShape redDivider;

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

	//Test
	float spawnTimer = 0.f;
	float maxTimer = 5.f;

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

