#pragma once
#include <SFML/Graphics.hpp>

class ActorObject
{
public:
	//Constructors and Destructors
	ActorObject();
	~ActorObject();

	virtual void Begin();
	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f pos);

	float getRotation() const;
	void setRotation(float rot);

protected:
	sf::Vector2f position;
	float rotation;
};

