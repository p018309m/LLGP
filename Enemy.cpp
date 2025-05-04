#include "Enemy.h"

Enemy::Enemy()
{
	//Sprite Render Stuff
	characters = sf::Image("assets/enemy.png");
	if(!characterText.loadFromImage(characters))
		std::cout << "Failed to Load Image" << std::endl;
	spritey.setTextureRect({ { 0,0 }, { 20,20 } });
	spritey.setOrigin({ spritey.getTextureRect().size.x / 2.f, spritey.getTextureRect().size.y / 2.f });
	enemyPos = sf::Vector2f(100.f, 100.f);
	enemyDirection = sf::degrees(0.f);
	spritey.scale(sf::Vector2f{ 2.f,2.f });

	//Collision Stuff
	body.setOrigin(spritey.getOrigin());
	body.setSize(sf::Vector2f(spritey.getScale().x * 15, spritey.getScale().y * 15));

	HealthCall::OnDeath.AddListener(this, std::bind(&Enemy::Handle_Death, this, std::placeholders::_1, std::placeholders::_2));
}

Enemy::~Enemy()
{
}

void Enemy::Begin()
{
	//Components Add
	collisionComp = Enemy::AddComponent<Collision>(this, body, ColliderTag::Workers, GetID());
	healthComp = Enemy::AddComponent<HealthComponent>(this, 10.f);
	actualSpeed = speed;
}

void Enemy::Render(sf::RenderWindow& window)
{
	ActorObject::Render(window);
	if (active)
	{
		spritey.setPosition(enemyPos);
		ActorObject::Render(window);
		body.setFillColor(sf::Color::Blue);
		window.draw(body);
	}
}

void Enemy::Update(float deltaTime)
{
	if (!active)
		return;
	ActorObject::Update(deltaTime);
	body.setPosition(spritey.getPosition());
	body.setRotation(spritey.getRotation());
}

void Enemy::CollisionUpdate(CollisionManager& collisionManager)
{
	for (Collision* other : collisionManager.GetAllColliders())
	{
		if (other == this->collisionComp) continue;

		if (collisionComp->CheckCollision(*other))
		{
			switch (other->GetTag())
			{
			case ColliderTag::Warriors:
				this->PushActorObject(other->GetPosition(), 1.f);
				break;
			case ColliderTag::Projectile:
				this->healthComp->DamageHealth(this, 10.f);
				ScorePoints::OnAddScore(150.f);
				break;
			}
		}
	}
}

void Enemy::Activate(sf::Vector2f position)
{
	active = true;
	spritey.setPosition(position);
}

void Enemy::FollowPlayer(sf::Vector2f& playerPos)
{
	sf::Vector2f direction = playerPos - this->getPosition();
	float normalised = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (normalised != 0)
		direction /= normalised;
	if (normalised < 400.f)
		actualSpeed = speed;
	else if (normalised < 700.f)
		actualSpeed = speed * .75f;
	else
		actualSpeed = speed * .45f;
	enemyPos += direction * actualSpeed;
	this->setPosition(enemyPos);
}

void Enemy::Handle_Death(ActorObject* objectHit, int val)
{
	if (objectHit != this)
		return;
	Deactivate();
}
