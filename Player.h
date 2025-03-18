#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Input.h"

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

	void Handle_MoveUp(sf::Keyboard::Key key);
	void Handle_MoveDown(sf::Keyboard::Key key);
	void Handle_MoveLeft(sf::Keyboard::Key key);
	void Handle_MoveRight(sf::Keyboard::Key key);

private:
	float UpdatePlayerRotation(float targetRot, float currentRot, float time);
	sf::VertexArray drawArray;
	std::unique_ptr<Input> input;
};

