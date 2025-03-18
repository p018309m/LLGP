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
}

Game::Game()
{
	this->InitialiseVariables();
	this->InitialiseWindow();
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

	view.setCenter(mainPlayer.spritey.getPosition());

	timeSincePhysicsStep += deltaTime;
	while (timeSincePhysicsStep > physicsTimeStep)
	{
		mainPlayer.GetCollision().CheckCollision(enemy.GetCollision(), 20.f);
		enemy.GetCollision().CheckCollision(mainPlayer.GetCollision(), 10.f);
		totalTimeFixed += 1;
		timeSincePhysicsStep -= physicsTimeStep;
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
			mainPlayer.Update(gameEvent, *this->window);
			enemy.Update(gameEvent, *this->window);
			totalTimeTicked += 1;
			timeSinceTick = 0.f;
		}
	}
	totalTimeFree += 1;
	
}

void Game::Update()
{
	this->PollEvents();
}

void Game::Render()
{
	window->setView(view);
	this->window->clear();
	mainPlayer.Draw(*this->window);
	enemy.Draw(*this->window);
	this->window->display();
}
