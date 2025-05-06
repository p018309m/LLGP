#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"
#include <iostream>

enum class ColliderTag {Default, Player, Workers, Warriors, Projectile, Sinistar, Crystal, Bombs, Asteroid};

class Collision : public Component
{
public:
	//Constructor and Destructor
	Collision(ActorObject* object, sf::Shape& body, ColliderTag tag, int id);
	virtual ~Collision() = default;

	ColliderTag GetTag() const { return tag; }
	int GetID() const { return id; }

	void Move(float dx, float dy) {
		body.move(sf::Vector2f(dx, dy));
	}

	bool GetActive() { return isActive; }
	void SetActive(bool toSet) { isActive = toSet; }

	bool CheckCollision(Collision other);
	sf::Vector2f GetPosition() { return body.getGlobalBounds().position; }
	sf::Vector2f GetSize() { return body.getGlobalBounds().size; }

	ActorObject* GetOwner() { return this->_object; }

private:
	sf::Shape& body;
	ColliderTag tag = ColliderTag::Default;
	int id = -1;
	bool isActive;
};

