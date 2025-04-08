#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(std::shared_ptr<ActorObject> object, const sf::Texture& texture, int frameWidth, int frameHeight, float frameTime) : Component(object), spriteSheet(texture), frameTime(frameTime)
{
	
}

void AnimationComponent::Update(float deltaTime)
{
    if (!isPlaying || frame.empty()) return;

    elapsedTime += deltaTime;
    if (elapsedTime >= frameTime) {
        elapsedTime = 0.f;
        currentFrame++;
        if (currentFrame >= frame.size()) {
            if (looping) currentFrame = 0;
            else {
                currentFrame = frame.size() - 1;
                isPlaying = false;
            }
        }
        spriteSheet.setTextureRect(frame[currentFrame]);
    }
    std::cout << "Hello" << std::endl;
    spriteSheet.setPosition(_object->getPosition());
    spriteSheet.setRotation(sf::degrees(_object->getRotation()));
}

void AnimationComponent::Play()
{
    isPlaying = true;
    currentFrame = 0;
    elapsedTime = 0.f;
}

void AnimationComponent::Stop()
{
    isPlaying = false;
}

void AnimationComponent::SetLoop(bool loop)
{
    looping = loop;
}
