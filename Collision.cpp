#include "Collision.h"

Collision::Collision(sf::RectangleShape& body) : body(body)
{
	
}

Collision::~Collision()
{

}

bool Collision::CheckCollision(Collision other, float push)
{
	
	int val = 0;
	sf::Vector2f otherPosition = other.GetPosition() + sf::Vector2f({ other.body.getOrigin().x, -other.body.getOrigin().y });
	sf::Vector2f otherSize = other.GetSize();
	sf::Vector2f thisPosition = GetPosition() + sf::Vector2f({ body.getOrigin().x, -body.getOrigin().y });
	sf::Vector2f thisSize = GetSize();

	bool collisionX = (thisPosition.x >= otherPosition.x && thisPosition.x <= otherPosition.x + otherSize.x) ||
		(thisPosition.x + thisSize.x >= otherPosition.x && thisPosition.x + thisSize.x <= otherPosition.x + otherSize.x);
		
	bool collisionY = (thisPosition.y >= otherPosition.y && thisPosition.y <= otherPosition.y + otherSize.y) ||
		(thisPosition.y + thisSize.y >= otherPosition.y && thisPosition.y + thisSize.y <= otherPosition.y + otherSize.y);

	if (collisionX && collisionY)
		val += 1;

	std::cout << val << std::endl;

	return collisionX && collisionY;
	
	/***
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetSize() / 2.f;
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetSize() / 2.f;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
	sf::Vector2f thisSize = GetSize();

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
	***/
}
