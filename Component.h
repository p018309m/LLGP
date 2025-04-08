#pragma once
#include <SFML/Graphics.hpp>
#include "ActorObject.h"

class ActorObject;

class Component {
public:
	Component(std::shared_ptr<ActorObject> object) : object(object) {}
	~Component() = default;

	virtual void Update(float deltaTime) {}
	
protected:
	std::shared_ptr<ActorObject> object;
};