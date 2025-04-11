#include "Enemy.h"

Enemy::Enemy()
{
	enemySpritey.setOrigin(sf::Vector2{ 10.f,12.f });
	enemyPos = sf::Vector2f(20.f, 20.f);
	enemyDirection = sf::degrees(0.f);
	enemySpritey.scale(sf::Vector2f{ 2.f,2.f });
	body.setOrigin(enemySpritey.getScale() * 5.f);
	body.setSize(sf::Vector2f(enemySpritey.getScale().x * 10, enemySpritey.getScale().y * 6));

	collisionComp = Enemy::AddComponent<Collision>(this, body);
}

Enemy::~Enemy()
{

}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(enemySpritey);
	body.setFillColor(sf::Color::Blue);
	window.draw(body);
}

void Enemy::Update()
{
	//enemySpritey.setPosition(body.getPosition());
	body.setPosition(enemySpritey.getPosition());
	//enemySpritey.setRotation(enemySpritey.getRotation() + sf::degrees(1.f));
	body.setRotation(enemySpritey.getRotation());
}
