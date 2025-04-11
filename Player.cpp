#include "Player.h"

Player::Player()
{
	spritey.setOrigin(sf::Vector2{ 9.f,9.f });
	playerPos = sf::Vector2f(500.f, 500.f);
	playerDirection = sf::degrees(0.f);
	spritey.scale(sf::Vector2f{ 2.5f,2.5f });
	body.setOrigin(spritey.getScale() * 2.f);
	body.setSize(sf::Vector2f(spritey.getScale().x * 8, spritey.getScale().y * 4));
	input = std::make_unique<Input>();

	input->OnMoveUp.AddListener(this, std::bind(&Player::Handle_MoveUp, this, std::placeholders::_1));
	input->OnMoveDown.AddListener(this, std::bind(&Player::Handle_MoveDown, this, std::placeholders::_1));
	input->OnMoveLeft.AddListener(this, std::bind(&Player::Handle_MoveLeft, this, std::placeholders::_1));
	input->OnMoveRight.AddListener(this, std::bind(&Player::Handle_MoveRight, this, std::placeholders::_1));
	input->OnShoot.AddListener(this, std::bind(&Player::Handle_Shoot, this, std::placeholders::_1));

	animComp = Player::AddComponent<AnimationComponent>(this, characterText, sf::Vector2u(18,18), 2.f);
}

Player::~Player()
{
	Player::RemoveComponent(animComp);
}

void Player::Begin()
{

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(spritey);
	body.setFillColor(sf::Color::Red);
	window.draw(body);
}

void Player::Update(float deltaTime)
{
	ActorObject::Update(deltaTime);
	input->HandleInput();
	body.setPosition(spritey.getPosition());
	body.setRotation(spritey.getRotation());
}

void Player::FixedUpdate()
{
	//spritey.setPosition(spritey.getPosition() + velocity);
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

void Player::Handle_Shoot(sf::Mouse::Button key)
{

}

float Player::UpdatePlayerRotation(float targetRot, float currentRot, float time)
{
	float angle = std::fmod(targetRot - currentRot + 540.f, 360.f) - 180.f;
	return currentRot + angle * time;
}
