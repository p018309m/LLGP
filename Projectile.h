#pragma once
#include <SFML/Graphics.hpp>

class Projectile
{
public:
	//Constructor
	Projectile();

	void Fire(sf::Vector2f pos, sf::Vector2f dir);
	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);
	bool isActive() { return active; }
	void Deactivate();
	sf::Vector2f getVelocity() { return velocity; }
	void setSpeed(float newSpeed) { projSpeed = newSpeed; }
	bool active;

private:
	sf::CircleShape shape;
	float projSpeed = 0.005f;
	sf::Vector2f velocity;

	float timer = 0.f;
	float lifeSpan = 1.f;

};

