#include "Game.h"

void Game::InitialiseVariables()
{
	this->window = nullptr;
	lastTime = std::chrono::steady_clock::now();
}

void Game::InitialiseWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ 1280, 720 }), "Sinistar");
	view = window->getDefaultView();
	starPool.view = view;
	starPool.Init();

	hudWindow = window->getDefaultView();
	hudWindow.setViewport(sf::FloatRect({ 0.f, 0.f }, { 1.f,1.f }));
}

sf::Vector2f Game::UpdateCameraMovement(float time, sf::View view, const Player& player)
{
	sf::Vector2f currentPos = view.getCenter();
	sf::Vector2f targetPos = player.getPosition();
	sf::Vector2f playerVelocity = (targetPos - currentPos) / deltaTime;

	float lag = .5f;
	sf::Vector2f followOffset = (targetPos - currentPos) * lag;

	float velocityUse = 0.05f;
	sf::Vector2f velocityOffset = playerVelocity * velocityUse;

	return currentPos + followOffset + velocityOffset;
}

Game::Game()
{
	this->InitialiseVariables();
	this->InitialiseWindow();
	if (!font.openFromFile("assets/font/Run, Coward.ttf")) 
	{
		std::cout << "Failed to load font!" << std::endl;
		return;  // Handle error appropriately
	}
	playerHUD = new PlayerHUD(font, mainPlayer.hudTexture);
}

Game::~Game()
{
	this->window.reset();
}

const bool Game::getGameRunning() const
{
	return this->window->isOpen();
}

void Game::PollEvents()
{
	currentTime = std::chrono::steady_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count();
	lastTime = currentTime;
	timeSincePhysicsStep += deltaTime;
	while (timeSincePhysicsStep > physicsTimeStep)
	{
		totalTimeFixed += 1;
		timeSincePhysicsStep -= physicsTimeStep;
		enemy.Update();
		mainPlayer.Update(deltaTime);
		mainPlayer.FixedUpdate(deltaTime);
		mainPlayer.GetCollision().CheckCollision(enemy.GetCollision());
		view.setCenter(UpdateCameraMovement(deltaTime, view, mainPlayer));
	}

	if (timeSinceTick < tickLength)
	{
		timeSinceTick += deltaTime;
	}
	else
	{
		while (std::optional<sf::Event> gameEvent = this->window->pollEvent())
		{
			if (gameEvent->is<sf::Event::Closed>())
				this->window->close();
			totalTimeTicked += 1;
			timeSinceTick = 0.f;
		}
	}
	totalTimeFree += 1;
	
}

void Game::Update()
{
	this->PollEvents();
	starPool.view = view;
	starPool.Update();
}

void Game::Render()
{
	window->setView(view);
	this->window->clear();
	asteroid.Draw(*this->window);
	enemy.Render(*this->window);
	mainPlayer.Render(*this->window);
	starPool.Render(*this->window);
	playerHUD->Render(*this->window);
	this->window->display();
}
