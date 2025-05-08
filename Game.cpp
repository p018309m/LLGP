#include "Game.h"

void Game::InitialiseVariables()
{
	this->window = nullptr;
	lastTime = std::chrono::steady_clock::now();

	//collision init
	collisionManager = std::make_unique<CollisionManager>();

	//enemy init
	enemyManager = std::make_unique<EnemyManager>(50);
	enemyManager->Begin();

	//asteroid init
	asteroidManager = std::make_unique<AsteroidManager>(10);
	asteroidManager->Begin();

	//player init
	mainPlayer = std::make_unique<Player>();
	mainPlayer->Begin();

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

Game::Game()
{
	this->InitialiseVariables();
	this->InitialiseWindow();
	playerHUD = std::make_unique<PlayerHUD>();
	for (auto& enemy : enemyManager->GetAllEnemies())
		collisionManager->AddCollider(enemy->GetCollision());

	collisionManager->AddCollider(mainPlayer->GetCollision());

	for (auto& proj : mainPlayer->GetShootComp()->GetAllProjectiles())
		collisionManager->AddCollider(proj->GetCollision());

	for (auto& bomb : mainPlayer->GetShootComp()->GetAllBombs())
		collisionManager->AddCollider(bomb->GetCollision());

	for (auto& asteroid : asteroidManager->GetAllAsteroids())
	{
		collisionManager->AddCollider(asteroid->GetCollision());
		for (auto& crystal : asteroid->GetAllCrystals())
			collisionManager->AddCollider(crystal->GetCollision());
	}
}

Game::~Game()
{
	this->window.reset();
	collisionManager->Clear();
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

		//enemies update
		enemyManager->PositionUpdate(mainPlayer->getPosition());
		enemyManager->Update(deltaTime);
		enemyManager->CollisionUpdate(*collisionManager);

		asteroidManager->PositionUpdate(mainPlayer->getPosition());
		asteroidManager->Update(deltaTime);
		asteroidManager->CollisionUpdate(*collisionManager);

		//player update
		mainPlayer->Update(deltaTime);
		mainPlayer->FixedUpdate(deltaTime);
		mainPlayer->CollisionUpdate(*collisionManager);

		//views update
		view.setCenter(UpdateCameraMovement(deltaTime, view, *mainPlayer));
		minimapView.setCenter(UpdateCameraMovement(deltaTime, view, *mainPlayer));
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
	starPool->view = view;
	starPool->Update();
}

void Game::Render()
{
	this->window->clear();

	//MainView
	window->setView(view);
	starPool->Render(*this->window);
	asteroidManager->Render(*this->window);
	mainPlayer->Render(*this->window);
	enemyManager->Render(*this->window);

	//HUDView
	this->window->setView(hudView);
	this->window->draw(divider);
	this->window->draw(redDivider);
	playerHUD->Render(*this->window);
	this->window->draw(borderSprite);

	//MinimapView
	this->window->setView(minimapView);
	asteroidManager->Render(*this->window);
	enemyManager->Render(*this->window);
	mainPlayer->Render(*this->window);

	this->window->display();
}
