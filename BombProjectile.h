#pragma once
#include "Projectile.h"
#include "AnimationComponent.h"

class BombProjectile : public Projectile, public ActorObject
{
public:
	BombProjectile();

	void Fire(sf::Vector2f pos, sf::Vector2f dir) override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window) override;
	bool isActive() override { return active; }
	void Deactivate();

private:
	sf::Image bombImage;
	sf::Texture bombText;
	sf::Sprite bombey = sf::Sprite(bombText);

	AnimationComponent* animComp;
};

