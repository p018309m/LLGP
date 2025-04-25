#include "BombProjectile.h"

BombProjectile::BombProjectile()
{
	bombImage = sf::Image("assets/bombs.png");
	if (!bombText.loadFromImage(bombImage))
		return;
	bombey.setTextureRect({ { 0,0 }, { 10,10 } });
	bombey.setOrigin({ bombey.getTextureRect().size.x / 2.f, bombey.getTextureRect().size.y / 2.f });
	bombey.scale(sf::Vector2f{ 2.f,2.f });
	animComp = BombProjectile::AddComponent<AnimationComponent>(this, bombey, 10, .3f, 3);
}
void BombProjectile::Fire(sf::Vector2f pos, sf::Vector2f dir)
{
	Projectile::Fire(pos, dir);
	bombey.setPosition(pos);
}

void BombProjectile::Update(float deltaTime)
{
	animComp->Update(deltaTime);
	Projectile::Update(deltaTime);
	if (!isActive())
		return;
	bombey.move(Projectile::getVelocity() * deltaTime);
}

void BombProjectile::Render(sf::RenderWindow& window)
{
	if (isActive())
		window.draw(bombey);
}

void BombProjectile::Deactivate()
{
	Projectile::Deactivate();
}
