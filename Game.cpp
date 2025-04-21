#include "Game.h"

void Game::InitialiseVariables()
{
	this->window = nullptr;
	lastTime = std::chrono::steady_clock::now();
	
	//Init Stars
	for (int i = 0; i < 10; ++i)
	{
		Star s;
		s.position = sf::Vector2f(
			view.getCenter().x + rand() % 12000 - 6000,
			view.getCenter().y + rand() % 12000 - 6000);
		s.size = static_cast<float>(rand() % 2 + 1);
		stars.push_back(s);
	}
}

void Game::InitialiseWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ 1280, 720 }), "Sinistar");
	view = window->getDefaultView();
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
		//mainPlayer.GetCollision().CheckCollision(asteroid.GetCollision());
		//enemy.GetCollision().CheckCollision(mainPlayer.GetCollision(), 10.f);
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

	sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.f, view.getSize());

	for (Star& star : stars)
	{
		if (!viewBounds.contains(star.position))
		{
			star.position = sf::Vector2f(
				view.getCenter().x + rand() % 12000 - 6000,
				view.getCenter().y + rand() % 12000 - 6000);
		}
	}
}

void Game::Render()
{
	window->setView(view);
	this->window->clear();
	asteroid.Draw(*this->window);
	enemy.Render(*this->window);

	sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.f, view.getSize());

	for (Star& star : stars)
	{
		if (viewBounds.contains(star.position))
		{
			std::cout << "See" << std::endl;
			sf::CircleShape shape(star.size);
			shape.setFillColor(sf::Color::White);
			shape.setPosition(star.position);
			window->draw(shape);
		}
	}

	mainPlayer.Render(*this->window);
	this->window->display();
}
