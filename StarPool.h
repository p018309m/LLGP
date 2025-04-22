#pragma once
#include "SFML/Graphics.hpp"

struct Star {
	sf::Vector2f position;
	float size;
};
class StarPool
{
public:
	StarPool();
	void Init();
	void Update();
	void Render(sf::RenderWindow& window);

	sf::View view;

private:
	std::vector<Star> stars;
	int starNumberMax;
};

