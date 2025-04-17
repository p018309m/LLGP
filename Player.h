#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Input.h"
#include "ActorObject.h"
#include "AnimationComponent.h"
#include "Collision.h"

template<typename T>
bool NearlyEqual(T a, T b, T diff = static_cast<T>(1.f))
{
	return std::abs(a - b) < diff;
}

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
	const sf::Image characters = sf::Image("assets/shipanim.png");
	sf::Texture characterText;
	bool result = characterText.loadFromImage(characters);
	sf::Sprite spritey = sf::Sprite(characterText);

	void Handle_MoveUp(int val);
	void Handle_MoveDown(int val);
	void Handle_MoveLeft(int val);
	void Handle_MoveRight(int val);
	void Handle_Shoot(int val);

	Collision GetCollision() { return Collision(this, body); }

private:
	float UpdatePlayerRotation(float targetRot, float currentRot, float time);
	sf::VertexArray drawArray;
	std::unique_ptr<Input> input;
	
	AnimationComponent* animComp;
	Collision* collisionComp;
};

