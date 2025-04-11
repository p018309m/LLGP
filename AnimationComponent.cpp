#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(ActorObject* object, sf::Texture& texture, sf::Vector2u imageCount, float frameTime) : Component(object), spriteSheet(texture), frameTime(frameTime)
{
    this->imageCount = imageCount;
    this->frameTime = frameTime;
    totalTime = 0.f;
    currentImage.x = 0;
    
    animRect.size.x = texture.getSize().x / float(imageCount.x);
    animRect.size.y = texture.getSize().y / float(imageCount.y);
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::Update(int row, float deltaTime)
{
    currentImage.y = row;
    totalTime += deltaTime;

    if (totalTime >= frameTime)
    {
        totalTime -= frameTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }

    animRect.position.x = currentImage.x * animRect.size.x;
    animRect.position.y = currentImage.y * animRect.size.y;
}

