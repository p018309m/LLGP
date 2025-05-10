#pragma once
#include <SFML/Graphics.hpp>
#include <concepts>
#include "Component.h"
#include <iostream>

class Component;

template<typename T>
concept isComponent = std::derived_from<T, Component> == true;

class ActorObject
{
public:
	//Constructors and Destructors
	ActorObject();
	virtual ~ActorObject();

	virtual void Begin();
	virtual void Update(float deltaTime);
	virtual void FixedUpdate(float deltaTime);
	virtual void Render(sf::RenderWindow& window);
	virtual void PushActorObject(const sf::Vector2f& contactPos, float force);

	virtual sf::Vector2f getPosition() const;
	virtual void setPosition(const sf::Vector2f pos);

	virtual float getRotation() const;
	virtual void setRotation(float rot);

	virtual sf::Vector2f getVelocity(){ return velocity; }
	virtual sf::Vector2f setVelocity(sf::Vector2f velocity);
	virtual sf::Vector2f addVelocity(sf::Vector2f velocity);

	virtual void setSpeed(float newSpeed) { this->speed = newSpeed; }

	sf::Sprite getSprite() const;

	template<typename T> requires isComponent<T> T* GetComponent()
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
	template<typename T, typename... Args> requires isComponent<T> T* AddComponent(Args&&... args)
	{
		std::unique_ptr<Component> newComp = std::make_unique<T>(std::forward<Args>(args)...);
		components.push_back(std::move(newComp));
		return static_cast<T*>(components.back().get());
	}
	template<typename T> requires isComponent<T> bool RemoveComponent(T* comp)
	{
		for (int i = 0; i < components.size(); ++i)
		{
			T* returnComp = nullptr;
			returnComp = static_cast<T*>(components[i].get());
			if (returnComp == comp)
			{
				components.erase(components.begin() + i);
				return true;
			}
		}
		return false;
	}

protected:
	sf::Vector2f position;
	sf::Vector2f velocity;
	float rotation;
	float speed;
	float maxVelocity;

	sf::Image characters;
	sf::Texture characterText;
	sf::Sprite spritey = sf::Sprite(characterText);

	std::string name;
	std::string tag;
	std::vector<std::unique_ptr<Component>> components;
};
