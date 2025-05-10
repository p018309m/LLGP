#include "Warriors.h"

Warriors::Warriors()
{
	characters = sf::Image("assets/warrior.png");
	if (!characterText.loadFromImage(characters))
		std::cout << "Failed to Load Image" << std::endl;
	spritey.setTextureRect({ { 0,0 }, { 30,34 } });
	spritey.setOrigin({ spritey.getTextureRect().size.x / 2.f, spritey.getTextureRect().size.y / 2.f });

	spritey.scale(sf::Vector2f{ 1.f,1.f });

	//Collision Stuff
	body.setOrigin(spritey.getOrigin());
	body.setSize(sf::Vector2f(spritey.getScale().x * 15, spritey.getScale().y * 15));
}

Warriors::~Warriors()
{
}

void Warriors::Begin()
{
	//Components Add
	collisionComp = Warriors::AddComponent<Collision>(this, body, ColliderTag::Warriors, GetID());
	healthComp = Warriors::AddComponent<HealthComponent>(this, 10.f);
	shootComp = Warriors::AddComponent<ShootingComponent>(this, 3, 0, .5f, 5.f);
	actualSpeed = speed;
}

void Warriors::Render(sf::RenderWindow& window)
{
	if (active)
	{
		ActorObject::Render(window);
		shootComp->Draw(window);
	}
}

void Warriors::FollowPlayer(sf::Vector2f& playerPos)
{
	Enemy::FollowPlayer(playerPos);
	ShootPlayer(playerPos);
}

void Warriors::ShootPlayer(sf::Vector2f playerLoc)
{
	sf::Vector2f directionToFace;
	directionToFace.x = playerLoc.x - spritey.getPosition().x;
	directionToFace.y = playerLoc.y - spritey.getPosition().y;

	spritey.setRotation(sf::radians(atan2(directionToFace.y, directionToFace.x)));
	body.setRotation(spritey.getRotation());
	sf::Vector2f spriteDirection = sf::Vector2f(std::cos(spritey.getRotation().asRadians()), std::sin(spritey.getRotation().asRadians()));
	if(NearlyEqualAngle(atan2(directionToFace.y, directionToFace.x), 3.f))
		shootComp->Shoot(spriteDirection);
}

void Warriors::Update(float deltaTime)
{
	if (!active)
		return;
	ActorObject::Update(deltaTime);
	body.setPosition(spritey.getPosition());
	body.setRotation(spritey.getRotation());
	shootComp->Update(deltaTime);
}

void Warriors::CollisionUpdate(CollisionManager& collisionManager)
{
	shootComp->CollisionUpdate(collisionManager);
	if (collisionComp->GetActive())
	{
		for (Collision* other : collisionManager.GetAllColliders())
		{
			if (other == this->collisionComp) continue;

			if (collisionComp->CheckCollision(*other))
			{
				switch (other->GetTag())
				{
				case ColliderTag::Player:
					this->PushActorObject(other->GetPosition(), 1.f);
					break;
				case ColliderTag::Workers:
					if (other->GetActive())
						this->PushActorObject(other->GetPosition(), 1.f);
					break;
				case ColliderTag::Warriors:
					if (other->GetActive())
						this->PushActorObject(other->GetPosition(), 1.f);
					break;
				case ColliderTag::Asteroid:
					if (other->GetActive())
						this->PushActorObject(other->GetPosition(), 1.f);
					break;
				case ColliderTag::Projectile:
					if (other->GetActive())
					{
						this->healthComp->DamageHealth(this, 10.f);
						ScorePoints::OnAddScore(500.f);
					}
					break;
				}
			}
		}
	}
}

void Warriors::Handle_Death(ActorObject* objectHit, int val)
{
	if (objectHit != this)
		return;
	Deactivate();
	collisionComp->SetActive(false);
}

void Warriors::Activate(sf::Vector2f position)
{
	active = true;
	enemyPos = position;
	collisionComp->SetActive(true);
	this->setPosition(position);
}
