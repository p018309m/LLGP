#include "Player.h"

Player::Player()
{
	//Initial Sprite
	characters = sf::Image("assets/shipanim.png");
	if (!characterText.loadFromImage(characters))
		std::cout << "Failed to Load Image" << std::endl;
	spritey.setTextureRect({ { 0,0 }, { 22,22 } });
	spritey.setOrigin({ spritey.getTextureRect().size.x / 2.f, spritey.getTextureRect().size.y / 2.f });
	spritey.scale(sf::Vector2f{ 2.5f,2.5f });
	speed = 0.1f;

	//Collision Box
	body.setOrigin({ spritey.getTextureRect().size.x / 2.f, spritey.getTextureRect().size.y / 2.f });
	body.setSize(sf::Vector2f(spritey.getScale().x * 8, spritey.getScale().y * 4));

	//Input Stuff
	input = std::make_unique<Input>();
	input->OnMoveUp.AddListener(this, std::bind(&Player::Handle_MoveUp, this, std::placeholders::_1));
	input->OnMoveDown.AddListener(this, std::bind(&Player::Handle_MoveDown, this, std::placeholders::_1));
	input->OnMoveLeft.AddListener(this, std::bind(&Player::Handle_MoveLeft, this, std::placeholders::_1));
	input->OnMoveRight.AddListener(this, std::bind(&Player::Handle_MoveRight, this, std::placeholders::_1));
	input->OnShoot.AddListener(this, std::bind(&Player::Handle_Shoot, this, std::placeholders::_1));

	//Components Adding
	animComp = Player::AddComponent<AnimationComponent>(this, spritey, 22, .3f, 3);
	collisionComp = Player::AddComponent<Collision>(this, body);
	shootComp = Player::AddComponent<ShootingComponent>(this, 15, 0.1f);
}

Player::~Player()
{
	Player::RemoveComponent(animComp);
	Player::RemoveComponent(collisionComp);
}

void Player::Begin()
{

}

void Player::Render(sf::RenderWindow& window)
{
	ActorObject::Render(window);
	body.setFillColor(sf::Color::Red);
	window.draw(body);
	shootComp->Draw(window);
}

void Player::Update(float deltaTime)
{
	curVelocity = sf::Vector2f(0.f, 0.f);
	ActorObject::Update(deltaTime);
	input->HandleInput();
	animComp->Update(deltaTime);
	shootComp->Update(deltaTime);
}

void Player::FixedUpdate(float deltaTime)
{
	ActorObject::FixedUpdate(deltaTime);
	addVelocity(curVelocity);
	body.setPosition(spritey.getPosition());
	body.setRotation(spritey.getRotation());
}

void Player::Handle_MoveUp(int val)
{
	curVelocity.y -= speed;
	if (!NearlyEqual(spritey.getRotation().asDegrees(), 270.0f))
	{
		std::cout << spritey.getRotation().asDegrees() << std::endl;
		spritey.setRotation(sf::degrees(UpdatePlayerRotation(270.0f, spritey.getRotation().asDegrees(), .25f)));
	}
}

void Player::Handle_MoveDown(int val)
{
	curVelocity.y += speed;
	if (!NearlyEqual(spritey.getRotation().asDegrees(), 90.0f))
	{
		spritey.setRotation(sf::degrees(UpdatePlayerRotation(90.0f, spritey.getRotation().asDegrees(), .25f)));
	}
}

void Player::Handle_MoveLeft(int val)
{
	curVelocity.x -= speed;
	if (!NearlyEqual(spritey.getRotation().asDegrees(), 180.0f))
	{
		spritey.setRotation(sf::degrees(UpdatePlayerRotation(180.0f, spritey.getRotation().asDegrees(), .25f)));
	}
}

void Player::Handle_MoveRight(int val)
{
	curVelocity.x += speed;
	if (!NearlyEqual(spritey.getRotation().asDegrees(), 0.0f))
	{
		spritey.setRotation(sf::degrees(UpdatePlayerRotation(0.0f, spritey.getRotation().asDegrees(), .25f)));
	}
}

void Player::Handle_Shoot(int val)
{
	sf::Vector2f spriteDirection = sf::Vector2f(std::cos(spritey.getRotation().asRadians()), std::sin(spritey.getRotation().asRadians()));
	shootComp->Shoot(spriteDirection);
}

float Player::UpdatePlayerRotation(float targetRot, float currentRot, float time)
{
	
	float angle = std::fmod(targetRot - currentRot + 540.f, 360.f) - 180.f;
	if (angle > 0.f)
		animComp->PlayAnimation(4, 9);
	else if (angle < 0.f)
		animComp->PlayAnimation(10, 15);
	return currentRot + angle * time;
}
