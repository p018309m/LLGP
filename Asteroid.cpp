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

void Asteroid::MoveAsteroid()
{
}

void Asteroid::Handle_Death(ActorObject* objectHit, int val)
{
	if (objectHit != this)
		return;
	Deactivate();
	std::cout << "AsteroidDeath" << std::endl;
	ScorePoints::OnAddScore(150.f);
}

void Asteroid::Begin()
{
	collisionComp = Asteroid::AddComponent<Collision>(this, body, ColliderTag::Asteroid, GetID());
	healthComp = Asteroid::AddComponent<HealthComponent>(this, 10.f);
	actualSpeed = speed;
}

void Asteroid::Render(sf::RenderWindow& window)
{
	ActorObject::Render(window);
	if (active)
	{
		spritey.setPosition(asteroidPos);
		ActorObject::Render(window);
		body.setFillColor(sf::Color::Blue);
		window.draw(body);
	}
}

void Asteroid::Update(float deltaTime)
{
	if (!active)
		return;
	ActorObject::Update(deltaTime);
	body.setPosition(spritey.getPosition());
	body.setRotation(spritey.getRotation());
}

void Asteroid::CollisionUpdate(CollisionManager& collisionManager)
{
	for (Collision* other : collisionManager.GetAllColliders())
	{
		if (other == this->collisionComp) continue;

		if (collisionComp->CheckCollision(*other))
		{
			switch (other->GetTag())
			{
			case ColliderTag::Projectile:
				this->healthComp->DamageHealth(this, 10.f);
				break;
			}
		}
	}
}

void Asteroid::Activate(sf::Vector2f position)
{
	active = true;
	spritey.setPosition(position);
}
