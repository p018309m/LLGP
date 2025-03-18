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
	input->BroadcastOnMoveUp(1);
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
	if (const auto* keyPressed = gameEvent->getIf<sf::Event::KeyPressed>())
	{
		/*if(keyPressed->scancode == sf::Keyboard::Scan::D)
		{
			spritey.setPosition(spritey.getPosition() + sf::Vector2f(3.f,.0f));
		}
		if (keyPressed->scancode == sf::Keyboard::Scan::A)
		{
			spritey.setPosition(spritey.getPosition() + sf::Vector2f(-3.f, .0f));
		}
		if (keyPressed->scancode == sf::Keyboard::Scan::W)
		{
			spritey.setPosition(spritey.getPosition() + sf::Vector2f(.0f, -3.f));
		}
		if (keyPressed->scancode == sf::Keyboard::Scan::S)
		{
			spritey.setPosition(spritey.getPosition() + sf::Vector2f(.0f, 3.f));
		}*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			spritey.setPosition(spritey.getPosition() + sf::Vector2f(-3.f, .0f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			spritey.setPosition(spritey.getPosition() + sf::Vector2f(3.f, .0f));
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			spritey.setPosition(spritey.getPosition() + sf::Vector2f(.0f, 3.f));
		}
	}
	spritey.setRotation(sf::degrees(UpdatePlayerRotation(window)));
}

void Player::Handle_MoveUp(int in)
{
	std::cout << "Handle_MoveUp called with arg: " << in << std::endl;
	spritey.setPosition(spritey.getPosition() + sf::Vector2f(.0f, -3.f));
}

float Player::UpdatePlayerRotation(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	float angle = atan2(mousePos.y - spritey.getPosition().y, mousePos.x - spritey.getPosition().x) * (180.0 / 3.141592653589793238463);
	return angle;
}
