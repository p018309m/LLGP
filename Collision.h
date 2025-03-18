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
		std::cout << "Collision Hit" << std::endl;
	}

	bool CheckCollision(Collision other, float push);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfHeight() { return body.getSize() / 2.f; }

private:
	sf::RectangleShape& body;
};

