#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"

template<typename T>
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

	template<typename T> requires isComponent<T> T* GetComponent();
	template<typename T> requires isComponent<T> T* AddComponent();
	template<typename T> requires isComponent<T> bool RemoveComponent(T* comp);

protected:
	sf::Vector2f position;
	float rotation;
	std::string name;
	std::string tag;
	std::vector<std::unique_ptr<Component>> components;
};
