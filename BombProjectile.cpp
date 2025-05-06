#include "BombProjectile.h"

BombProjectile::BombProjectile()
{
	characters = sf::Image("assets/bombs.png");
	if (!characterText.loadFromImage(characters))
		return;
	spritey.setTextureRect({ { 0,0 }, { 10,10 } });
	spritey.setOrigin({ spritey.getTextureRect().size.x / 2.f, spritey.getTextureRect().size.y / 2.f });
	spritey.scale(sf::Vector2f{ 2.f,2.f });
	animComp = BombProjectile::AddComponent<AnimationComponent>(this, spritey, 10, .3f, 3);
}

void BombProjectile::Fire(sf::Vector2f pos, sf::Vector2f dir)
{
	Projectile::Fire(pos, dir);
	spritey.setPosition(pos);
}

void BombProjectile::Update(float deltaTime)
{
	animComp->Update(deltaTime);
	Projectile::Update(deltaTime);
	if (!isActive())
		return;
	spritey.move(Projectile::getVelocity() * deltaTime);
}

void BombProjectile::Render(sf::RenderWindow& window)
{
	if (isActive())
		window.draw(spritey);
}

void BombProjectile::Deactivate()
{
	Projectile::Deactivate();
}
