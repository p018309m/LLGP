#include "Asteroid.h"

Asteroid::Asteroid()
{
	asteroidSpritey.setOrigin(sf::Vector2{ 10.f,12.f });
	asteroidPos = sf::Vector2f(20.f, 20.f);
	asteroidDirection = sf::degrees(0.f);
	asteroidSpritey.scale(sf::Vector2f{ 2.f,2.f });
	//body.setSize(sf::Vector2f(asteroidSpritey.getScale().x * 10, asteroidSpritey.getScale().y * 6));
	body.setOrigin(asteroidSpritey.getScale() * 9.f);
	body.setRadius(45.f);
}

Asteroid::~Asteroid()
{

}

void Asteroid::Draw(sf::RenderWindow& window)
{
	window.draw(asteroidSpritey);
	body.setFillColor(sf::Color::Blue);
	window.draw(body);
}

void Asteroid::Update()
{
	//enemySpritey.setPosition(body.getPosition());
	body.setPosition(asteroidSpritey.getPosition());
	//enemySpritey.setRotation(enemySpritey.getRotation() + sf::degrees(1.f));
	body.setRotation(asteroidSpritey.getRotation());
}
