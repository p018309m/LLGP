#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(ActorObject* object, sf::Texture& texture, sf::Vector2u imageCount, float frameTime) : Component(object), spriteSheet(texture), frameTime(frameTime)
{
    this->imageCount = imageCount;
    this->frameTime = frameTime;
    totalTime = 0.f;
    currentImage.x = 0;
    
}

AnimationComponent::~AnimationComponent()
{
}

