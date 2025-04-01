#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Input.h"
#include "Collision.h"

class Player
{
public:
	//Constructors and Destructors
	Player();
	virtual ~Player();

	//Functions
	void Draw(sf::RenderWindow& window);
	void Update();
	void FixedUpdate();
	
	//Variables
	sf::Vector2f playerPos;
	sf::Angle playerDirection;
	sf::RectangleShape body;
	sf::Vector2f velocity;

	//Texture
	const sf::Image characters = sf::Image("assets/spaceship.png");
	sf::Texture characterText;
	bool result = characterText.loadFromImage(characters, false, sf::IntRect({ 0,0 }, { 21, 18 }));
	sf::Sprite spritey = sf::Sprite(characterText);

	void Handle_MoveUp(sf::Keyboard::Key key);
	void Handle_MoveDown(sf::Keyboard::Key key);
	void Handle_MoveLeft(sf::Keyboard::Key key);
	void Handle_MoveRight(sf::Keyboard::Key key);
	void Handle_Shoot(sf::Mouse::Button key);

	Collision GetCollision() { return Collision(body); }

private:
	float UpdatePlayerRotation(float targetRot, float currentRot, float time);
	sf::VertexArray drawArray;
	std::unique_ptr<Input> input;
	
};

