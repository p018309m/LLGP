#include "BombProjectile.h"

BombProjectile::BombProjectile()
{
	characters = sf::Image("assets/bombs.png");
	if (!characterText.loadFromImage(characters))
		return;
	spritey.setTextureRect({ { 0,0 }, { 10,10 } });
	spritey.setOrigin({ spritey.getTextureRect().size.x / 2.f, spritey.getTextureRect().size.y / 2.f });
	spritey.scale(sf::Vector2f{ 2.f,2.f });
	animComp = BombProjectile::AddComponent<AnimationComponent>(this, spritey, 10, .3f, 3);
}

BombProjectile::~BombProjectile()
{
	RemoveComponent(collisionComp);
	RemoveComponent(animComp);
}

void BombProjectile::Begin()
{
	collisionComp = Projectile::AddComponent<Collision>(this, body, ColliderTag::Projectile, GetID());
	body.setSize(sf::Vector2f(shape.getRadius() * collisionSizeMultiplier, shape.getRadius() * collisionSizeMultiplier));
	body.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
}

void BombProjectile::Fire(sf::Vector2f pos, sf::Vector2f dir)
{
	Projectile::Fire(pos, dir);
	spritey.setPosition(pos);
}

void BombProjectile::Update(float deltaTime)
{
	if (!isActive())
		return;
	animComp->Update(deltaTime);
	Projectile::Update(deltaTime);
	spritey.move(Projectile::getVelocity() * deltaTime);
}

void BombProjectile::Render(sf::RenderWindow& window)
{
	if (isActive())
		window.draw(spritey);
}

void BombProjectile::CollisionUpdate(CollisionManager& collisionManager)
{
	/*if (!isActive())
		return;
	for (Collision* other : collisionManager.GetAllColliders())
	{
		if (other == this->GetCollision()) continue;

		if (GetCollision()->CheckCollision(*other))
		{
			switch (other->GetTag())
			{
			case ColliderTag::Workers:
				if (other->GetActive())
				{
					HealthCall::OnDeath(other->GetOwner(), 1);
					this->Deactivate();
				}
				break;
			case ColliderTag::Warriors:
				if (other->GetActive())
				{
					HealthCall::OnDeath(other->GetOwner(), 1);
					this->Deactivate();
				}
				break;
			case ColliderTag::Asteroid:
				if (other->GetActive())
					this->PushActorObject(other->GetPosition(), 1.f);
				break;
			}
		}
	}*/
}

void BombProjectile::Deactivate()
{
	Projectile::Deactivate();
}
