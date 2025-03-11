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
	while (const std::optional event = this->window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			this->window->close();
	}
}

void Game::Update()
{
	this->PollEvents();
}

void Game::Render()
{
	this->window->clear(sf::Color(255, 0, 0, 255));

	this->window->display();
}
