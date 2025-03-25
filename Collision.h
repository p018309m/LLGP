#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Collision
{
public:
	//Constructor and Destructor
	Collision(sf::RectangleShape& body);
	~Collision();

	void Move(float dx, float dy) {
		body.move(sf::Vector2f(dx, dy));
	}

	bool CheckCollision(Collision other);
	sf::Vector2f GetPosition() { return body.getGlobalBounds().position; }
	sf::Vector2f GetSize() { return body.getGlobalBounds().size; }

private:
	sf::RectangleShape& body;
};

