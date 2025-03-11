#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	//Constructors and Destructors
	Player();
	virtual ~Player();

	//Functions
	void Draw(sf::RenderWindow& window);
	
	//Variables
	sf::Vector2f playerPos;
	sf::Angle playerDirection;

private:
	sf::VertexArray drawArray;
};

