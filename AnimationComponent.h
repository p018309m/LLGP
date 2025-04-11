#pragma once
#include "SFML/Graphics.hpp"
#include "Component.h"
#include <iostream>

class AnimationComponent : public Component
{
private:

public:
	//Constructors & Destructors
	AnimationComponent(ActorObject* object, sf::Texture& texture, sf::Vector2u imageCount, float frameTime);
	~AnimationComponent();

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	sf::IntRect animRect;

	float totalTime;
	float frameTime;
	sf::Texture spriteSheet;
};

