#pragma once
#include "SFML/Graphics.hpp"
#include "Component.h"
#include <iostream>

class AnimationComponent : public Component
{
public:
	//Constructors & Destructors
	AnimationComponent(ActorObject* object, sf::Sprite& spritey, int texInc, float frameTime, int endFrame);
	~AnimationComponent() = default;

	void Update(float deltaTime);
	void PlayAnimation(int startFrame, int endFrame);

private:
	int texWidth;
	int texIncrement;
	int endFrame;
	float totalTime;
	float frameTime;
	sf::Sprite& spriteSheet;

	//singleAnim
	int lastFrame;
	int firstFrame;
	bool isPlaying = false;
};

