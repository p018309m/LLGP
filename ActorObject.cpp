#include "ActorObject.h"

ActorObject::ActorObject() : position(0, 0), rotation(0)
{
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

void ActorObject::Render(sf::RenderWindow& window)
{
}


sf::Vector2f ActorObject::getPosition() const
{
	return position;
}

void ActorObject::setPosition(const sf::Vector2f pos)
{
	position = pos;
}

float ActorObject::getRotation() const
{
	return rotation;
}

void ActorObject::setRotation(float rot)
{
	rotation = rot;
}
