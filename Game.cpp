#include "Game.h"

void Game::InitialiseVariables()
{
	this->window = nullptr;
	lastTime = std::chrono::steady_clock::now();
	collisionManager = std::make_unique<CollisionManager>();
	enemyManager = std::make_unique<EnemyManager>(10);
	enemyManager->Begin();
	mainPlayer = std::make_unique<Player>();
	mainPlayer->Begin();
	asteroid = std::make_unique<Asteroid>();
	starPool = std::make_unique<StarPool>();
}

void Game::InitialiseWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Sinistar");
	view = window->getDefaultView();
	starPool->view = view;
	starPool->Init();

	hudView = window->getDefaultView();
	hudView.setViewport(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }));

	minimapView = window->getDefaultView();
	minimapView.setViewport(sf::FloatRect({ 0.445f, 0.067f }, { 0.13f, 0.13f }));

	redDivider.setSize(sf::Vector2f((float)window->getSize().x, 5.f));
	redDivider.setPosition(sf::Vector2f(0.f, (float)WINDOW_HEIGHT * .21f));
	redDivider.setFillColor(sf::Color(228, 10, 11));

	divider.setSize(sf::Vector2f((float)window->getSize().x, (float)WINDOW_HEIGHT * .21f));
	divider.setFillColor(sf::Color::Black);

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

void Game::UpdateCollision()
{
	collisionManager->CheckCollisions([](Collision* a, Collision* b) 
		{
			auto tagA = a->GetTag();
			auto tagB = b->GetTag();

			if ((tagA == ColliderTag::Player && tagB == ColliderTag::Workers) ||
				(tagB == ColliderTag::Player && tagA == ColliderTag::Workers))
			{
				std::cout << "HIT HIT" << std::endl;
			}
		});
}

Game::Game()
{
	this->InitialiseVariables();
	this->InitialiseWindow();
	playerHUD = std::make_unique<PlayerHUD>();
	collisionManager->AddCollider(mainPlayer->GetCollision());
	for (auto& enemy : enemyManager->GetAllEnemies())
		collisionManager->AddCollider(enemy->GetCollision());
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
		//enemy.Update(deltaTime);
		enemyManager->Update(deltaTime);
		mainPlayer->Update(deltaTime);
		mainPlayer->FixedUpdate(deltaTime);
		view.setCenter(UpdateCameraMovement(deltaTime, view, *mainPlayer));
		minimapView.setCenter(UpdateCameraMovement(deltaTime, view, *mainPlayer));

		//Test
		spawnTimer += 0.1f;
		if (spawnTimer >= maxTimer)
		{
			spawnTimer = 0.f;
			enemyManager->SpawnEnemy(sf::Vector2f(rand() % 800, 0));
		}
	}

	if (timeSinceTick < tickLength)
	{
		timeSinceTick += deltaTime;
		UpdateCollision();
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
	starPool->view = view;
	starPool->Update();
}

void Game::Render()
{
	this->window->clear();

	//MainView
	window->setView(view);
	asteroid->Draw(*this->window);
	//enemy.Render(*this->window);
	mainPlayer->Render(*this->window);
	starPool->Render(*this->window);
	enemyManager->Render(*this->window);

	//HUDView
	this->window->setView(hudView);
	this->window->draw(divider);
	this->window->draw(redDivider);
	playerHUD->Render(*this->window);
	this->window->draw(borderSprite);

	//MinimapView
	this->window->setView(minimapView);
	asteroid->Draw(*this->window);
	//enemy.Render(*this->window);
	mainPlayer->Render(*this->window);

	this->window->display();
}
