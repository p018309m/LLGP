#pragma once
#include <SFML/Graphics.hpp>
#include "ActorObject.h"

class ActorObject;

class Component {
public:
	Component(ActorObject* object) : _object(object) {}
	virtual ~Component() {}

	virtual void Update(float deltaTime) {}
	
protected:
	ActorObject* _object;
};