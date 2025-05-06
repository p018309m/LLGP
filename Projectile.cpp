#include "Projectile.h"

Projectile::Projectile()
{
	shape.setRadius(5.f);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));

	timer = 0.f;
}

Projectile::~Projectile()
{
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
	if (!isActive())
		return;
	for (Collision* other : collisionManager.GetAllColliders())
	{
		if (other == this->collisionComp) continue;

		if (collisionComp->CheckCollision(*other))
		{
			switch (other->GetTag())
			{
			case ColliderTag::Workers:
				HealthCall::OnDeath(other->GetOwner(), 1);
				this->Deactivate();
				break;
			case ColliderTag::Player:
				if (owner != other->GetOwner())
				{
					HealthCall::OnDeath(other->GetOwner(), 1);
					std::cout << "This Owner: " << owner << " Other Owner: " << other->GetOwner() << std::endl;
					this->Deactivate();
				}
				break;
			}
		}
	}
}

void Projectile::Begin()
{
	collisionComp = Projectile::AddComponent<Collision>(this, body, ColliderTag::Projectile, GetID());
	body.setSize(sf::Vector2f(shape.getRadius() * collisionSizeMultiplier, shape.getRadius() * collisionSizeMultiplier));
	body.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
}

void Projectile::Update(float deltaTime)
{
	if (!isActive())
		return;
	curVelocity = sf::Vector2f(0.f, 0.f);
	timer += 0.01f;
	if (timer >= lifeSpan)
		Deactivate();
}

void Projectile::Render(sf::RenderWindow& window)
{
	if(isActive())
		window.draw(shape);
}

void Projectile::FixedUpdate(float deltaTime)
{
	if (!isActive())
		return;
	position += velocity;
	shape.setPosition(position);
	addVelocity(curVelocity);
	//std::cout<<position
	body.setPosition(shape.getPosition());
	body.setRotation(shape.getRotation());
}

void Projectile::Deactivate()
{
	collisionComp->SetActive(false);
	active = false;
	curVelocity = sf::Vector2f(0.f, 0.f);
	shape.setPosition(sf::Vector2f(0.f, 0.f));
	timer = 0.f;
}
