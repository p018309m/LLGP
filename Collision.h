#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"
#include <iostream>

class Collision : public Component
{
public:
	//Constructor and Destructor
	Collision(ActorObject* object, sf::Shape& body);
	~Collision();

	void Move(float dx, float dy) {
		body.move(sf::Vector2f(dx, dy));
	}

	bool CheckCollision(Collision other);
	sf::Vector2f GetPosition() { return body.getGlobalBounds().position; }
	sf::Vector2f GetSize() { return body.getGlobalBounds().size; }

private:
	sf::Shape& body;
};

