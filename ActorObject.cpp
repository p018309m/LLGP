#include "ActorObject.h"

ActorObject::ActorObject() : position(0, 0), rotation(0)
{
	spritey.setTexture(characterText);
}

ActorObject::~ActorObject()
{
	//components.clear();
}

void ActorObject::Begin()
{

}

void ActorObject::Update(float deltaTime)
{
}

void ActorObject::FixedUpdate(float deltaTime)
{
	position += velocity;
	spritey.setPosition(position);
}

void ActorObject::Render(sf::RenderWindow& window)
{
	window.draw(spritey);
}


sf::Vector2f ActorObject::getPosition() const
{
	return position;
}

void ActorObject::setPosition(const sf::Vector2f pos)
{
	position = pos;
	spritey.setPosition(position);
}

float ActorObject::getRotation() const
{
	return rotation;
}

void ActorObject::setRotation(float rot)
{
	rotation = rot;
}

sf::Vector2f ActorObject::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
	return this->velocity;
}

sf::Vector2f ActorObject::addVelocity(sf::Vector2f velocity)
{
	this->velocity += velocity;
	return this->velocity;
}

sf::Sprite ActorObject::getSprite() const
{
	return spritey;
}
