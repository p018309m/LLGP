#include "Projectile.h"

Projectile::Projectile()
{
	shape.setRadius(5.f);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
	timer = 0.f;
	lifeSpan = 0.5f;
}

Projectile::~Projectile()
{
}

void Projectile::Fire(sf::Vector2f pos, sf::Vector2f dir)
{
	active = true;
	velocity = dir * projSpeed;
	shape.setPosition(pos);
	ScorePoints::OnAddScore(20);
	timer = 0.f;
}

void Projectile::Begin()
{
	collisionComp = Projectile::AddComponent<Collision>(this, body, ColliderTag::Projectile, GetID());
}

void Projectile::Update(float deltaTime)
{
	if (!isActive())
		return;
	shape.move(velocity * deltaTime);
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
}

void Projectile::Deactivate()
{
	active = false;
	timer = 0.f;
}
