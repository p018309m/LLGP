#include "Crystal.h"

Crystal::Crystal()
{
	shape.setRadius(5.f);
	shape.setFillColor(sf::Color::Yellow);
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));

	body.setOrigin(shape.getOrigin());
	body.setSize(sf::Vector2f(shape.getRadius(), shape.getRadius()));
}

Crystal::~Crystal()
{
}

void Crystal::Begin()
{
	collisionComp = Crystal::AddComponent<Collision>(this, body, ColliderTag::Crystal, GetID());
}

void Crystal::Update(float deltaTime)
{
	if (!isActive())
		return;
	shape.move(velocity * deltaTime);
	body.setPosition(shape.getPosition());
	timer += 0.01f;
	if (timer >= lifeSpan)
		Deactivate();
}

void Crystal::Render(sf::RenderWindow& window)
{
	if (isActive())
		window.draw(shape);
}

void Crystal::GetSent(sf::Vector2f position, sf::Vector2f direction)
{
	collisionComp->SetActive(true);
	active = true;
	velocity = direction * speed;
	shape.setPosition(position);
	timer = 0.f;
}

void Crystal::Deactivate()
{
	active = false;
	timer = 0.f;
	collisionComp->SetActive(false);
}
