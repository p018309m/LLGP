#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Input.h"
#include "ActorObject.h"
#include "AnimationComponent.h"
#include "Collision.h"
#include "ShootingComponent.h"

//Nearly Equal Template
template<typename T>
bool NearlyEqual(T a, T b, T diff = static_cast<T>(.5f))
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
	void Render(sf::RenderWindow& window);
	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	
	//Variables
	sf::Vector2f playerPos;
	sf::Angle playerDirection;
	sf::RectangleShape body;

	//Input Handles
	void Handle_MoveUp(int val);
	void Handle_MoveDown(int val);
	void Handle_MoveLeft(int val);
	void Handle_MoveRight(int val);
	void Handle_Thrust(int val);
	void Handle_Shoot(int val);

	Collision GetCollision() { return Collision(this, body); }

private:
	float UpdatePlayerRotation(float targetRot, float currentRot, float time);
	sf::VertexArray drawArray;
	std::unique_ptr<Input> input;
	sf::Vector2f curVelocity;
	
	AnimationComponent* animComp;
	Collision* collisionComp;
	ShootingComponent* shootComp;
};

