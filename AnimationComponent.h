#pragma once
#include "SFML/Graphics.hpp"
#include "Component.h"

class AnimationComponent : public Component
{
private:

public:
	//Constructors & Destructors
	AnimationComponent(std::shared_ptr<ActorObject> object, const sf::Texture& texture, int frameWidth, int frameHeight, float frameTime);
	
	void Update(float deltaTime) override;
	
	void Play();
	void Stop();
	void SetLoop(bool loop);

private:
	sf::Sprite spriteSheet;
	std::vector<sf::IntRect> frame;
	int currentFrame = 0;
	float frameTime;
	float elapsedTime = 0.f;
	bool isPlaying = true;
	bool looping = true;
};

