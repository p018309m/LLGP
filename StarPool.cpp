#include "StarPool.h"
#include <iostream>

StarPool::StarPool()
{
	starNumberMax = 50;
}

void StarPool::Init()
{
	//Init Stars
	for (int i = 0; i < starNumberMax; ++i)
	{
		Star s;
		s.position = sf::Vector2f(
			view.getCenter().x + rand() % 12000 - 6000,
			view.getCenter().y + rand() % 12000 - 6000);
		s.size = (float)(rand() % 2 + 1);
		stars.push_back(s);
	}
}

void StarPool::Update()
{
	sf::FloatRect viewBounds(view.getCenter() - (view.getSize() * 2.f) / 2.f, (view.getSize() * 2.f));

	for (Star& star : stars)
	{
		if (!viewBounds.contains(star.position))
		{
			star.position = sf::Vector2f(
				view.getCenter().x + rand() % 12000 - 6000,
				view.getCenter().y + rand() % 12000 - 6000);
		}
	}
}

void StarPool::Render(sf::RenderWindow& window)
{
	sf::FloatRect viewBounds(view.getCenter() - (view.getSize() * 2.f) / 2.f, (view.getSize() * 2.f));

	for (Star& star : stars)
	{
		if (viewBounds.contains(star.position))
		{
			sf::CircleShape shape(star.size);
			shape.setFillColor(sf::Color::White);
			shape.setPosition(star.position);
			window.draw(shape);
		}
	}
}
