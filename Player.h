#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Input.h"
#include "ActorObject.h"
#include "AnimationComponent.h"
#include "Collision.h"

class Player : public ActorObject
{
public:
	//Constructors and Destructors
	Player();
	virtual ~Player();

	//Functions
	void Begin();
	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
	void FixedUpdate();
	
	//Variables
	sf::Vector2f playerPos;
	sf::Angle playerDirection;
	sf::RectangleShape body;
	sf::Vector2f velocity;

	//Texture
	const sf::Image characters = sf::Image("assets/shipspritesheet.png");
	sf::Texture characterText;
	bool result = characterText.loadFromImage(characters, false, sf::IntRect({ 0,0 }, {704 , 22 }));
	sf::Sprite spritey = sf::Sprite(characterText);

	void Handle_MoveUp(sf::Keyboard::Key key);
	void Handle_MoveDown(sf::Keyboard::Key key);
	void Handle_MoveLeft(sf::Keyboard::Key key);
	void Handle_MoveRight(sf::Keyboard::Key key);
	void Handle_Shoot(sf::Mouse::Button key);

	Collision GetCollision() { return Collision(this, body); }

private:
	float UpdatePlayerRotation(float targetRot, float currentRot, float time);
	sf::VertexArray drawArray;
	std::unique_ptr<Input> input;
	
	AnimationComponent* animComp;
	Collision* collisionComp;
};

