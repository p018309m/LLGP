#include "Game.h"

void Game::InitialiseVariables()
{
	this->window = nullptr;
	lastTime = std::chrono::steady_clock::now();
}

void Game::InitialiseWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Sinistar");
	view = window->getDefaultView();
	starPool.view = view;
	starPool.Init();

	hudView = window->getDefaultView();
	hudView.setViewport(sf::FloatRect({ 0.f, 0.f }, { 1.f,1.f }));

	minimapView = window->getDefaultView();
	minimapView.setViewport(sf::FloatRect({ 0.45f, 0.037f }, { 0.13f, 0.13f }));

	borderSprite.setTexture(borderTexture);
	borderSprite.setOrigin(sf::Vector2f(borderTexture.getSize().x / 4.f, 0.f));
	borderSprite.setScale(sf::Vector2f(2.f, 2.f));
	borderSprite.setPosition(sf::Vector2f(window->getSize().x * .45f, 0.f));
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
	playerHUD = std::make_unique<PlayerHUD>();
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
		minimapView.setCenter(UpdateCameraMovement(deltaTime, view, mainPlayer));
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
	this->window->clear();

	//MainView
	window->setView(view);
	asteroid.Draw(*this->window);
	enemy.Render(*this->window);
	mainPlayer.Render(*this->window);
	starPool.Render(*this->window);

	//HUDView
	this->window->setView(hudView);
	playerHUD->Render(*this->window);
	this->window->draw(borderSprite);

	//MinimapView
	this->window->setView(minimapView);
	asteroid.Draw(*this->window);
	enemy.Render(*this->window);
	mainPlayer.Render(*this->window);

	this->window->display();
}
