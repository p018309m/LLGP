#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(ActorObject* object, sf::Sprite& spritey, int texInc, float frameTime, int endFrame) : Component(object), spriteSheet(spritey), texIncrement(texInc), frameTime(frameTime), endFrame(endFrame)
{
    totalTime = 0.f;
    texWidth = 0;
}

void AnimationComponent::Update(float deltaTime)
{
    totalTime += deltaTime;
    if (isPlaying)
    {
        
        if (totalTime >= frameTime)
        {
            texWidth += texIncrement;

            if (texWidth >= lastFrame * texIncrement)
                isPlaying = false;

            if (texWidth < lastFrame * texIncrement)
                spriteSheet.setTextureRect({ {texWidth,0}, {texIncrement, texIncrement} });

            totalTime = 0.f;
        }
        return;
    }

    else
    {
        if (totalTime >= frameTime)
        {
            texWidth += texIncrement;

            if (texWidth >= endFrame * texIncrement)
                texWidth = 0;

            if (texWidth < endFrame * texIncrement)
                spriteSheet.setTextureRect({ { texWidth,0 }, { texIncrement,texIncrement } });

            totalTime = 0.f;
        }
    }
    
}

void AnimationComponent::PlayAnimation(int startFrame, int endFrame)
{
    firstFrame = startFrame;
    lastFrame = endFrame;
    texWidth = firstFrame * texIncrement;
    spriteSheet.setTextureRect({ { texWidth, 0 }, { texIncrement, texIncrement } });
    isPlaying = true;
    totalTime = 0.f;
}
