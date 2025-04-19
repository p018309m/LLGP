#include "Projectile.h"
#include <iostream>

Projectile::Projectile()
{
	shape.setRadius(5.f);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
	active = false;
}

void Projectile::Fire(sf::Vector2f pos, sf::Vector2f dir)
{
	shape.setPosition(pos);
	velocity = dir * speed;
	active = true;
}

void Projectile::Update(float deltaTime)
{
	if (active)
		shape.move(velocity * deltaTime);
}

void Projectile::Render(sf::RenderWindow& window)
{
	//if (active)
		window.draw(shape);
}

bool Projectile::isActive() const
{
	return active;
}

void Projectile::Deactivate()
{
	active = false;
}
