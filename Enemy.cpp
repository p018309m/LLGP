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
	body.setOrigin(spritey.getScale() * 5.f);
	body.setSize(sf::Vector2f(spritey.getScale().x * 10, spritey.getScale().y * 6));

	//Components Add
	collisionComp = Enemy::AddComponent<Collision>(this, body);
}

Enemy::~Enemy()
{

}

void Enemy::Render(sf::RenderWindow& window)
{
	spritey.setPosition(enemyPos);
	ActorObject::Render(window);
	body.setFillColor(sf::Color::Blue);
	window.draw(body);
}

void Enemy::Update()
{
	//spritey.setPosition(body.getPosition());
	body.setPosition(spritey.getPosition());
	//spritey.setRotation(spritey.getRotation() + sf::degrees(1.f));
	body.setRotation(spritey.getRotation());
}
