#include "Player.h"

Player::Player()
{
	playerPos = sf::Vector2f(500.f, 500.f);
	playerDirection = sf::degrees(45.f);
	spritey.scale(sf::Vector2f{ 1.f,1.f });
	spritey.setOrigin(sf::Vector2{ 9.f,9.f });
	input = std::make_unique<Input>();
	//Draw Triangle As Sprite
	/*drawArray = sf::VertexArray(sf::PrimitiveType::TriangleStrip, 3);
	drawArray[0].position = sf::Vector2f(0.f, -15.f);
	drawArray[1].position = sf::Vector2f(-15.f, 30.f);
	drawArray[2].position = sf::Vector2f(15.f, 30.f);

	for (size_t i = 0; i < drawArray.getVertexCount(); i++)
	{
		drawArray[i].color = sf::Color::White;
	}*/

	input->OnMoveUp.AddListener(this, std::bind(&Player::Handle_MoveUp, this, std::placeholders::_1));
	input->OnMoveDown.AddListener(this, std::bind(&Player::Handle_MoveDown, this, std::placeholders::_1));
	input->OnMoveLeft.AddListener(this, std::bind(&Player::Handle_MoveLeft, this, std::placeholders::_1));
	input->OnMoveRight.AddListener(this, std::bind(&Player::Handle_MoveRight, this, std::placeholders::_1));

}

Player::~Player()
{

}

void Player::Draw(sf::RenderWindow& window)
{
	sf::Transform transform;
	transform.translate(playerPos).rotate(playerDirection);
	window.draw(drawArray, transform);
	window.draw(spritey);
}

void Player::Update(std::optional<sf::Event> gameEvent, sf::RenderWindow& window)
{
	input->HandleInput(gameEvent, window);
}

void Player::Handle_MoveUp(sf::Keyboard::Key key)
{
	spritey.setPosition(spritey.getPosition() + sf::Vector2f(.0f, -3.f));
	spritey.setRotation(sf::degrees(UpdatePlayerRotation(270.f, spritey.getRotation().asDegrees(), .25f)));
}

void Player::Handle_MoveDown(sf::Keyboard::Key key)
{
	spritey.setPosition(spritey.getPosition() + sf::Vector2f(.0f, 3.f));
	spritey.setRotation(sf::degrees(UpdatePlayerRotation(90.f, spritey.getRotation().asDegrees(), .25f)));
}

void Player::Handle_MoveLeft(sf::Keyboard::Key key)
{
	spritey.setPosition(spritey.getPosition() + sf::Vector2f(-3.f, .0f));
	spritey.setRotation(sf::degrees(UpdatePlayerRotation(180.f, spritey.getRotation().asDegrees(), .25f)));
}

void Player::Handle_MoveRight(sf::Keyboard::Key key)
{
	spritey.setPosition(spritey.getPosition() + sf::Vector2f(3.f, .0f));
	spritey.setRotation(sf::degrees(UpdatePlayerRotation(0.f, spritey.getRotation().asDegrees(), .25f)));
}

float Player::UpdatePlayerRotation(float targetRot, float currentRot, float time)
{
	float angle = std::fmod(targetRot - currentRot + 540.f, 360.f) - 180.f;
	return currentRot + angle * time;
}
