#include "Asteroid.h"

Asteroid::Asteroid()
{
	characters = sf::Image("assets/asteroid.png");
	if (!characterText.loadFromImage(characters))
		std::cout << "Failed to Load Image" << std::endl;
	spritey.setTextureRect({ { 0,0 }, { 52,52 } });
	spritey.setOrigin({ spritey.getTextureRect().size.x / 2.f, spritey.getTextureRect().size.y / 2.f });
	spritey.setScale(sf::Vector2f{ 2.f,2.f });

	body.setOrigin(spritey.getOrigin());
	body.setSize(sf::Vector2f(spritey.getTextureRect().size.x, spritey.getTextureRect().size.y));

	HealthCall::OnDeath.AddListener(this, std::bind(&Asteroid::Handle_Death, this, std::placeholders::_1, std::placeholders::_2));
}

Asteroid::~Asteroid()
{
	
}

void Asteroid::MoveAsteroid(sf::Vector2f playerPos)
{
	sf::Vector2f direction = playerPos - this->getPosition();
	float normalised = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (normalised != 0)
		direction /= normalised;
	if (normalised > 1250.f)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_real_distribution<float> dist(-1000.0f, 1000.0f);
		float x = dist(gen);
		float y = dist(gen);
		asteroidPos = playerPos - sf::Vector2f(x,y);
	}
	asteroidPos += velocity * speed;
	this->setPosition(asteroidPos);
}

void Asteroid::SetVelocity()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * 3.14159265f);

	float angle = angleDist(gen);

	velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
}

void Asteroid::Handle_Death(ActorObject* objectHit, int val)
{
	if (objectHit != this)
		return;
	Deactivate();
	ScorePoints::OnAddScore(5.f);
	collisionComp->SetActive(false);
}

void Asteroid::SpawnCrystal(sf::Vector2f asteroidPos)
{
	Crystal* crystal = crystalPool->GetInactiveObjects();
	if (crystal)
	{
		crystal->Activate(asteroidPos);
		crystal->GetCollision()->SetActive(true);
		crystal->GetSent(asteroidPos, velocity.normalized());
	}
}

void Asteroid::Begin()
{
	collisionComp = Asteroid::AddComponent<Collision>(this, body, ColliderTag::Asteroid, GetID());
	healthComp = Asteroid::AddComponent<HealthComponent>(this, 100.f);
	crystalPool = std::make_unique<ObjectPoolCommon<Crystal>>(crystalNumber);
	actualSpeed = speed;

	int id = 0;
	for (auto& crystal : crystalPool->GetAllObjects())
	{
		crystal->Begin();
		crystal->SetID(id);
		crystal->setSpeed(1.f);
		crystal->SetLifeSpan(3.f);
		id++;
	}
}

void Asteroid::Render(sf::RenderWindow& window)
{
	if (active)
		ActorObject::Render(window);
}

void Asteroid::CrystalRender(sf::RenderWindow& window)
{
	crystalPool->Render(window);
}

void Asteroid::Update(float deltaTime)
{
	if (!active)
		return;
	//ActorObject::Update(deltaTime);
	body.setPosition(spritey.getPosition());
	body.setRotation(spritey.getRotation());
	crystalPool->Update(deltaTime);
}

void Asteroid::CollisionUpdate(CollisionManager& collisionManager)
{
	if(collisionComp->GetActive())
	{
		for (Collision* other : collisionManager.GetAllColliders())
		{
			if (other == this->collisionComp) continue;

			if (collisionComp->CheckCollision(*other))
			{
				switch (other->GetTag())
				{
				case ColliderTag::Projectile:
					if (other->GetActive())
					{
						this->healthComp->DamageHealth(this, 10.f);
						SpawnCrystal(asteroidPos);
					}
					break;
				case ColliderTag::Asteroid:
					if (other->GetActive())
						this->PushActorObject(other->GetPosition(), 1.f);
					break;
				case ColliderTag::Warriors:
					if (other->GetActive())
						this->PushActorObject(other->GetPosition(), 1.f);
					break;
				}
			}
		}
	}
}

void Asteroid::Activate(sf::Vector2f position)
{
	active = true;
	asteroidPos = position;
	spritey.setPosition(position);
	healthComp->AddHealth(50.f);
}
