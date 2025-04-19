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
	bool isActive() const;
	void Deactivate();

private:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	bool active;
	float speed = 0.01f;

};

