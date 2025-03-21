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

	bool CheckCollision(Collision other, float push);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetSize() { return body.getSize(); }

private:
	sf::RectangleShape& body;
};

