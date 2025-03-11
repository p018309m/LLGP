#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Player
{
public:
	//Constructors and Destructors
	Player();
	virtual ~Player();

	//Functions
	void Draw(sf::RenderWindow& window);
	void Update(std::optional<sf::Event> gameEvent, sf::RenderWindow& window);
	
	//Variables
	sf::Vector2f playerPos;
	sf::Angle playerDirection;

	//Texture
	const sf::Image characters = sf::Image("assets/sinistarsprites.jpg");
	sf::Texture characterText;
	bool result = characterText.loadFromImage(characters, false, sf::IntRect({ 0,0 }, { 18,18 }));
	sf::Sprite spritey = sf::Sprite(characterText);

private:
	float UpdatePlayerRotation(sf::RenderWindow& window);
	sf::VertexArray drawArray;
};

