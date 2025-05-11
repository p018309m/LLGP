#include "Crystal.h"

Crystal::Crystal()
{
	shape.setRadius(5.f);
	shape.setFillColor(sf::Color::Yellow);
	shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));

	body.setOrigin(shape.getOrigin());
	body.setSize(sf::Vector2f(shape.getRadius(), shape.getRadius()));

	HealthCall::OnDeath.AddListener(this, std::bind(&Crystal::Handle_Death, this, std::placeholders::_1, std::placeholders::_2));
}

Crystal::~Crystal()
{
	HealthCall::OnDeath.RemoveListener(this, std::bind(&Crystal::Handle_Death, this, std::placeholders::_1, std::placeholders::_2));
	RemoveComponent(collisionComp);
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
	collisionComp->Update(deltaTime);
	timer += 0.01f;
	if (timer >= lifeSpan)
		Deactivate();
}

void Crystal::Render(sf::RenderWindow& window)
{
	if (isActive())
	{
		window.draw(shape);
	}
}

void Crystal::GetSent(sf::Vector2f position, sf::Vector2f direction)
{
	//velocity = direction * speed;
	velocity = sf::Vector2f(0.f, 0.f);
	timer = 0.f;
}

void Crystal::Activate(sf::Vector2f position)
{
	active = true;
	shape.setPosition(position);
}

void Crystal::Deactivate()
{
	active = false;
	timer = 0.f;
	collisionComp->SetActive(false);
}

void Crystal::Handle_Death(ActorObject* objectHit, int health)
{
	if (objectHit != this)
		return;
	Deactivate();
}
