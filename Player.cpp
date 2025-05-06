 #include "Player.h"

Player::Player()
{
	//Initial Sprite
	characters = sf::Image("assets/shipanim.png");
	if (!characterText.loadFromImage(characters))
		std::cout << "Failed to Load Image" << std::endl;
	spritey.setTextureRect({ { 0,0 }, { 22,22 } });
	spritey.setOrigin({ spritey.getTextureRect().size.x / 2.f, spritey.getTextureRect().size.y / 2.f });
	spritey.scale(sf::Vector2f{ 2.5f,2.5f });
	speed = 0.1f;
	maxVelocity = 10.f;

	//Input Stuff
	input = std::make_unique<Input>();
	input->OnMoveUp.AddListener(this, std::bind(&Player::Handle_MoveUp, this, std::placeholders::_1));
	input->OnMoveDown.AddListener(this, std::bind(&Player::Handle_MoveDown, this, std::placeholders::_1));
	input->OnMoveLeft.AddListener(this, std::bind(&Player::Handle_MoveLeft, this, std::placeholders::_1));
	input->OnMoveRight.AddListener(this, std::bind(&Player::Handle_MoveRight, this, std::placeholders::_1));
	input->OnThrust.AddListener(this, std::bind(&Player::Handle_Thrust, this, std::placeholders::_1));
	input->OnShoot.AddListener(this, std::bind(&Player::Handle_Shoot, this, std::placeholders::_1));
	input->OnBombsAway.AddListener(this, std::bind(&Player::Handle_Bombs, this, std::placeholders::_1));

	//Scoring
	ScorePoints::OnAddScore.AddListener(this, std::bind(&Player::Handle_Score, this, std::placeholders::_1));
	HealthCall::OnDeath.AddListener(this, std::bind(&Player::Handle_Death, this, std::placeholders::_1, std::placeholders::_2));

	curLives = 3;
}

Player::~Player()
{
	Player::RemoveComponent(animComp);
	Player::RemoveComponent(collisionComp);
	Player::RemoveComponent(shootComp);
	Player::RemoveComponent(healthComp);

	input->OnMoveUp.RemoveListener(this, std::bind(&Player::Handle_MoveUp, this, std::placeholders::_1));
	input->OnMoveDown.RemoveListener(this, std::bind(&Player::Handle_MoveDown, this, std::placeholders::_1));
	input->OnMoveLeft.RemoveListener(this, std::bind(&Player::Handle_MoveLeft, this, std::placeholders::_1));
	input->OnMoveRight.RemoveListener(this, std::bind(&Player::Handle_MoveRight, this, std::placeholders::_1));
	input->OnThrust.RemoveListener(this, std::bind(&Player::Handle_Thrust, this, std::placeholders::_1));
	input->OnShoot.RemoveListener(this, std::bind(&Player::Handle_Shoot, this, std::placeholders::_1));
	input->OnBombsAway.RemoveListener(this, std::bind(&Player::Handle_Bombs, this, std::placeholders::_1));

	curBomb = 0;
}

void Player::Begin()
{
	//Collision Box
	body.setOrigin(spritey.getOrigin());
	body.setSize(sf::Vector2f(spritey.getScale().x * 8, spritey.getScale().y * 4));

	//Components Adding
	animComp = Player::AddComponent<AnimationComponent>(this, spritey, 22, .3f, 3);
	collisionComp = Player::AddComponent<Collision>(this, body, ColliderTag::Player, 0);
	shootComp = Player::AddComponent<ShootingComponent>(this, 25, 5, 0.05f, 5.f);
	healthComp = Player::AddComponent<HealthComponent>(this, 100.f);
}

void Player::Render(sf::RenderWindow& window)
{
	shootComp->Draw(window);
	ActorObject::Render(window);
	body.setFillColor(sf::Color::Red);
	window.draw(body);
}

void Player::Update(float deltaTime)
{
	curVelocity = sf::Vector2f(0.f, 0.f);
	ActorObject::Update(deltaTime);
	input->HandleInput();
	animComp->Update(deltaTime);
	shootComp->Update(deltaTime);
}

void Player::FixedUpdate(float deltaTime)
{
	ActorObject::FixedUpdate(deltaTime);
	addVelocity(curVelocity);
	body.setPosition(spritey.getPosition());
	body.setRotation(spritey.getRotation());
}

void Player::CollisionUpdate(CollisionManager& collisionManager)
{
	shootComp->CollisionUpdate(collisionManager);
	for (Collision* other : collisionManager.GetAllColliders())
	{
		if (other == this->collisionComp) continue;

		if (collisionComp->CheckCollision(*other))
		{
			switch (other->GetTag())
			{
			case ColliderTag::Workers:
				if(other->GetActive())
					this->PushActorObject(other->GetPosition(), 1.f);
				break;
			case ColliderTag::Asteroid:
				if (other->GetActive())
				{
					this->PushActorObject(other->GetPosition(), 1.f);
					break;
				}
			case ColliderTag::Crystal:
				if (other->GetActive())
				{
					this->AddBomb();
					break;
				}
			}
		}
	}
}

void Player::Handle_MoveUp(int val)
{
	curVelocity.y -= speed;
	if (!NearlyEqual(spritey.getRotation().asDegrees(), 270.0f))
	{
		spritey.setRotation(sf::degrees(UpdatePlayerRotation(270.0f, spritey.getRotation().asDegrees(), .25f)));
	}
}

void Player::Handle_MoveDown(int val)
{
	curVelocity.y += speed;
	if (!NearlyEqual(spritey.getRotation().asDegrees(), 90.0f))
	{
		spritey.setRotation(sf::degrees(UpdatePlayerRotation(90.0f, spritey.getRotation().asDegrees(), .25f)));
	}
}

void Player::Handle_MoveLeft(int val)
{
	curVelocity.x -= speed;
	if (!NearlyEqual(spritey.getRotation().asDegrees(), 180.0f))
	{
		spritey.setRotation(sf::degrees(UpdatePlayerRotation(180.0f, spritey.getRotation().asDegrees(), .25f)));
	}
}

void Player::Handle_MoveRight(int val)
{
	curVelocity.x += speed;
	if (!NearlyEqual(spritey.getRotation().asDegrees(), 360.0f))
	{
		spritey.setRotation(sf::degrees(UpdatePlayerRotation(0.0f, spritey.getRotation().asDegrees(), .25f)));
	}
}

void Player::Handle_Thrust(int val)
{
	if (curVelocity.x > 0.f) {
		curVelocity.x = std::max(curVelocity.x - 20.f, 0.f);
	}
	else if (curVelocity.x < 0.f) {
		curVelocity.x = std::min(curVelocity.x + 20.f, 0.f);
	}

	if (curVelocity.y > 0.f) {
		curVelocity.y = std::max(curVelocity.y - 20.f, 0.f);
	}
	else if (curVelocity.y < 0.f) {
		curVelocity.y = std::min(curVelocity.y + 20.f, 0.f);
	}
}

void Player::Handle_Shoot(int val)
{
	sf::Vector2f spriteDirection = sf::Vector2f(std::cos(spritey.getRotation().asRadians()), std::sin(spritey.getRotation().asRadians()));
	shootComp->Shoot(spriteDirection);
}

void Player::Handle_Bombs(int val)
{
	if (curBomb > 0)
	{
		sf::Vector2f spriteDirection = sf::Vector2f(std::cos(spritey.getRotation().asRadians()), std::sin(spritey.getRotation().asRadians()));
		shootComp->Bomb(spriteDirection);
		curBomb--;
	}
}

void Player::Handle_Score(int score)
{
	curScore += score;
	ScorePoints::OnScoreChange(this->curScore);
}

void Player::Handle_Death(ActorObject* objectHit, int health)
{
	if (objectHit != this)
		return;
	curLives--;
	HealthCall::OnLivesChange(curLives);
	if (curLives == 0)
		curLives = 3;
	
}

void Player::AddBomb()
{
	ScorePoints::OnAddScore(150.f);
	curBomb++;
}

float Player::UpdatePlayerRotation(float targetRot, float currentRot, float time)
{
	
	float angle = std::fmod(targetRot - currentRot + 540.f, 360.f) - 180.f;
	if (angle > 0.f)
		animComp->PlayAnimation(4, 9);
	else if (angle < 0.f)
		animComp->PlayAnimation(10, 15);
	return currentRot + angle * time;
}
