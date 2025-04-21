#include "Projectile.h"
#include <iostream>

Projectile::Projectile()
{
	shape.setRadius(5.f);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
	timer = 0.f;
	lifeSpan = 0.5f;
}

void Projectile::Fire(sf::Vector2f pos, sf::Vector2f dir)
{
	active = true;
	velocity = dir * speed;
	shape.setPosition(pos);
	timer = 0.f;
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
