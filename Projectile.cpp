#include "Projectile.h"

Projectile::Projectile()
{
	shape.setRadius(5.f);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));

	timer = 0.f;

	HealthCall::OnDeath.AddListener(this, std::bind(&Projectile::Handle_Death, this, std::placeholders::_1, std::placeholders::_2));
}

Projectile::~Projectile()
{
	HealthCall::OnDeath.RemoveListener(this, std::bind(&Projectile::Handle_Death, this, std::placeholders::_1, std::placeholders::_2));
	RemoveComponent(collisionComp);
}

void Projectile::Fire(sf::Vector2f pos, sf::Vector2f dir)
{
	collisionComp->SetActive(true);
	active = true;
	velocity = dir * projSpeed;
	shape.setPosition(pos);
	timer = 0.f;
}

void Projectile::CollisionUpdate(CollisionManager& collisionManager)
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
				case ColliderTag::Workers:
					if(other->GetActive())
					{
						HealthCall::OnDeath(other->GetOwner(), 1);
						ScorePoints::OnAddScore(150.f);
						this->Deactivate();
					}
					break;
				case ColliderTag::Projectile:
					if (other->GetActive())
					{
						HealthCall::OnDeath(this, 1);
						ScorePoints::OnAddScore(5.f);
						this->Deactivate();
					}
					break;
				case ColliderTag::Warriors:
					if (owner != other->GetOwner())
					{
						if(other->GetActive())
						{
							HealthCall::OnDeath(this, 1);
							HealthCall::OnDeath(other->GetOwner(), 1);
							ScorePoints::OnAddScore(500.f);
							this->Deactivate();
						}
					}
					break;
				case ColliderTag::Player:
					std::cout << other->GetOwner() << std::endl;
					if (owner != other->GetOwner())
					{
						HealthCall::OnDeath(this, 1);
						HealthCall::OnDeath(other->GetOwner(), 1);
						this->Deactivate();
					}
					break;

				}
			}
		}
	}
}

void Projectile::Begin()
{
	collisionComp = Projectile::AddComponent<Collision>(this, body, ColliderTag::Projectile, GetID());
	body.setSize(sf::Vector2f(shape.getRadius() * collisionSizeMultiplier, shape.getRadius() * collisionSizeMultiplier));
	body.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
	collisionComp->SetOwner(this->owner);
}

void Projectile::Update(float deltaTime)
{
	if (!isActive())
		return;
	shape.move(velocity * deltaTime);
	body.setPosition(shape.getPosition());
	timer += 0.01f;
	if (timer >= lifeSpan)
		Deactivate();
}

void Projectile::Render(sf::RenderWindow& window)
{
	if(isActive())
		window.draw(shape);
}

void Projectile::Handle_Death(ActorObject* objectHit, int val)
{
	if (objectHit != this)
		return;
	Deactivate();
	collisionComp->SetActive(false);
}

void Projectile::Deactivate()
{
	collisionComp->SetActive(false);
	active = false;
	timer = 0.f;
}
