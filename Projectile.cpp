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
	active = true;
	velocity = dir * projSpeed;
	shape.setPosition(pos);
	timer = 0.f;
}

void Projectile::CollisionUpdate(CollisionManager& collisionManager)
{
	for (Collision* other : collisionManager.GetAllColliders())
	{
		if (other == this->collisionComp) continue;

		if (collisionComp->CheckCollision(*other))
		{
			switch (other->GetTag())
			{
			case ColliderTag::Workers:
				HealthCall::OnDamageDealt(15.f);
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
	shape.move(velocity * deltaTime);
	body.setPosition(shape.getPosition());
	timer += 0.01f;
	if (timer >= lifeSpan)
	{
		Deactivate();
	}
}

void Projectile::Render(sf::RenderWindow& window)
{
	if(isActive())
		window.draw(shape);
	window.draw(body);
}

void Projectile::Deactivate()
{
	active = false;
	timer = 0.f;
}
