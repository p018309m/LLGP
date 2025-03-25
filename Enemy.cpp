#include "Enemy.h"

Enemy::Enemy()
{
	enemySpritey.setOrigin(sf::Vector2{ 9.f,9.f });
	enemyPos = sf::Vector2f(20.f, 20.f);
	enemyDirection = sf::degrees(0.f);
	enemySpritey.scale(sf::Vector2f{ 2.5f,2.5f });
	body.setOrigin(enemySpritey.getScale() * 2.f);
	body.setSize(sf::Vector2f(enemySpritey.getScale().x * 8, enemySpritey.getScale().y * 4));
	body.setPosition(enemySpritey.getGlobalBounds().position);
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

void Enemy::Update(std::optional<sf::Event> gameEvent, sf::RenderWindow& window)
{
	//enemySpritey.setPosition(body.getPosition());
}
