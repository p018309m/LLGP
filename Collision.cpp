#include "Collision.h"

Collision::Collision(sf::RectangleShape& body) : body(body)
{

}

Collision::~Collision()
{
}

bool Collision::CheckCollision(Collision other, float push)
{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfHeight();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfHeight();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.f && intersectY < 0.f)
	{
		push = std::min(std::max(push, 0.f), 1.f);
		if (intersectX > intersectY)
		{
			if (deltaX > 0.f)
			{
				Move(intersectX * (1.f - push), 0.f);
				other.Move(-intersectX * push, 0.f);
			}
			else
			{
				Move(-intersectX * (1.f - push), 0.f);
				other.Move(intersectX * push, 0.f);
			}
		}
		else
		{
			if (deltaY > 0.f)
			{
				Move(0.f, intersectY * (1.f - push));
				other.Move(0.f, -intersectY * push);
			}
			else
			{
				Move(0.f, -intersectY * (1.f - push));
				other.Move(0.f, intersectY * push);
			}
		}

		return true;
	}

	return false;
}
