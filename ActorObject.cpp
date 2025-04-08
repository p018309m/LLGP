#include "ActorObject.h"

ActorObject::ActorObject() : position(0, 0), rotation(0)
{
}

ActorObject::~ActorObject()
{
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

template<typename T> requires isComponent<T>
std::shared_ptr<T> ActorObject::GetComponent()
{
	T* returnComp = nullptr;
	for (int i = 0; i < components.size(); i++)
	{
		returnComp = static_cast<T*>(components[i].get());
		if (returnComp != nullptr)
		{
			break;
		}
	}
	return returnComp;
}

template<typename T> requires isComponent<T>
std::shared_ptr<T> ActorObject::AddComponent()
{
	std::unique_ptr<Component> newComp = std::make_unique<T>(this);
	components.push_back(std::move(newComp));
	return static_cast<T*>(components[components.size()].get());
}

template<typename T> requires isComponent<T>
bool ActorObject::RemoveComponent(std::shared_ptr<T> comp)
{
	/*for (int i = components.begin(); i != components.endl(); ++i)
	{
		T* returnComp = nullptr;
		returnComp = static_cast<T*>(components[i].get());
		if (returnComp != nullptr)
		{
			components.erase(i);
			return true;
		}
	}
	return false;*/
}
