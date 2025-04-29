#include "Enemy.h"

Enemy::Enemy()
{
	//Sprite Render Stuff
	characters = sf::Image("assets/enemy.png");
	if(!characterText.loadFromImage(characters))
		std::cout << "Failed to Load Image" << std::endl;
	spritey.setTextureRect({ { 0,0 }, { 20,20 } });
	spritey.setOrigin(sf::Vector2{ 10.f,12.f });
	enemyPos = sf::Vector2f(100.f, 100.f);
	enemyDirection = sf::degrees(0.f);
	spritey.scale(sf::Vector2f{ 2.f,2.f });

	//Collision Stuff
	body.setOrigin(spritey.getOrigin());
	body.setSize(sf::Vector2f(spritey.getScale().x * 10, spritey.getScale().y * 10));

	//Components Add
	collisionComp = Enemy::AddComponent<Collision>(this, body);
}

Enemy::~Enemy()
{

}

void Enemy::Render(sf::RenderWindow& window)
{
	ActorObject::Render(window);
	if (active)
	{
		spritey.setPosition(enemyPos);
		ActorObject::Render(window);
		body.setFillColor(sf::Color::Blue);
		window.draw(body);
	}
}

void Enemy::Update(float deltaTime)
{
	ActorObject::Update(deltaTime);
	if (!active)
		return;
	body.setPosition(spritey.getPosition());
	body.setRotation(spritey.getRotation());
}

void Enemy::Activate(sf::Vector2f position)
{
	active = true;
	spritey.setPosition(position);
}
