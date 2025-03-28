#include "Collision.h"

Collision::Collision(sf::Shape& body) : body(body)
{
	
}

Collision::~Collision()
{

}

bool Collision::CheckCollision(Collision other)
{
	
	int val = 0;
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherSize = other.GetSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisSize = GetSize();

	bool collisionX = (thisPosition.x >= otherPosition.x && thisPosition.x <= otherPosition.x + otherSize.x) ||
		(thisPosition.x + thisSize.x >= otherPosition.x && thisPosition.x + thisSize.x <= otherPosition.x + otherSize.x);
		
	bool collisionY = (thisPosition.y >= otherPosition.y && thisPosition.y <= otherPosition.y + otherSize.y) ||
		(thisPosition.y + thisSize.y >= otherPosition.y && thisPosition.y + thisSize.y <= otherPosition.y + otherSize.y);

	if (collisionX && collisionY)
		val += 1;

	std::cout << val << std::endl;

	return collisionX && collisionY;
}
