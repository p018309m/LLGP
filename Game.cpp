#include "Game.h"

void Game::InitialiseVariables()
{
	this->window = nullptr;
}

void Game::InitialiseWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ 1280, 720 }), "Sinistar");
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
	while (std::optional<sf::Event> gameEvent = this->window->pollEvent())
	{
		if (gameEvent->is<sf::Event::Closed>())
			this->window->close();
		mainPlayer.Update(gameEvent, *this->window);
	}
}

void Game::Update()
{
	this->PollEvents();
}

void Game::Render()
{
	this->window->clear();
	mainPlayer.Draw(*this->window);
	this->window->display();
}
