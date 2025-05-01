#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Input.h"
#include "ActorObject.h"
#include "AnimationComponent.h"
#include "ShootingComponent.h"
#include "HealthComponent.h"
#include "Collision.h"
#include "ScoreEvents.h"
#include "HealthCaller.h"

//Nearly Equal Template
template<typename T>
bool NearlyEqual(T a, T b, T diff = static_cast<T>(.1f))
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
	void Begin() override;
	void Render(sf::RenderWindow& window) override;
	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;
	
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
	void Handle_Bombs(int val);

	Collision* GetCollision() { return collisionComp; }


private:

	float UpdatePlayerRotation(float targetRot, float currentRot, float time);
	void Handle_Score(int score);
	void Handle_Death(int health);

	sf::VertexArray drawArray;
	std::unique_ptr<Input> input;
	sf::Vector2f curVelocity;
	
	AnimationComponent* animComp;
	Collision* collisionComp;
	ShootingComponent* shootComp;
	HealthComponent* healthComp;

	int curScore;
	int curLives;
};

