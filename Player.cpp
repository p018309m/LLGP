#include "Player.h"

Player::Player()
{
	playerPos = sf::Vector2f(500.f, 500.f);
	playerDirection = sf::degrees(45.f);
	drawArray = sf::VertexArray(sf::PrimitiveType::TriangleStrip, 3);
	drawArray[0].position = sf::Vector2f(0.f, -15.f);
	drawArray[1].position = sf::Vector2f(-15.f, 30.f);
	drawArray[2].position = sf::Vector2f(15.f, 30.f);

	for (size_t i = 0; i < drawArray.getVertexCount(); i++)
	{
		drawArray[i].color = sf::Color::White;
	}
}

Player::~Player()
{

}

void Player::Draw(sf::RenderWindow& window)
{
	sf::Transform transform;
	transform.translate(playerPos).rotate(playerDirection);
	window.draw(drawArray, transform);
}
