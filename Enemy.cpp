#include "Enemy.h"

Enemy::Enemy()
{
	//enemySpritey.setOrigin(sf::Vector2{ 9.f,9.f });
	enemyPos = sf::Vector2f(20.f, 20.f);
	enemyDirection = sf::degrees(0.f);
	enemySpritey.scale(sf::Vector2f{ 1.f,1.f });
	//body.setOrigin(sf::Vector2{ 9.f,9.f });
	body.setSize(sf::Vector2f(20.f, 20.f));
}

Enemy::~Enemy()
{

}

void Enemy::Draw(sf::RenderWindow& window)
{
	sf::Transform transform;
	transform.translate(enemyPos).rotate(enemyDirection);
	window.draw(enemySpritey, transform);
	//window.draw(body, transform);
}

void Enemy::Update(std::optional<sf::Event> gameEvent, sf::RenderWindow& window)
{
	enemySpritey.setPosition(body.getPosition());
}
