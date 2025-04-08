#pragma once
#include <SFML/Graphics.hpp>
#include <concepts>
#include "Component.h"

class Component;

template<class T>
concept isComponent = std::derived_from<T, Component> == true;

class ActorObject
{
public:
	//Constructors and Destructors
	ActorObject();
	~ActorObject();

	virtual void Begin();
	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f pos);

	float getRotation() const;
	void setRotation(float rot);

	template<typename T> requires isComponent<T> std::shared_ptr<T> GetComponent();
	template<typename T> requires isComponent<T> std::shared_ptr<T> AddComponent();
	template<typename T> requires isComponent<T> bool RemoveComponent(std::shared_ptr<T> comp);

protected:
	sf::Vector2f position;
	float rotation;
	std::string name;
	std::string tag;
	std::vector<std::unique_ptr<Component>> components;
};
