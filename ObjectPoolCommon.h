#pragma once
#include "SFML/Graphics.hpp"

template<typename T>
class ObjectPoolCommon
{
private:
	std::vector<std::unique_ptr<T>> objects;

public:
	ObjectPoolCommon(size_t size)
	{
		objects.reserve(size);
		for (size_t i = 0; i < size; ++i)
			objects.push_back(std::make_unique<T>());
	}

	T* GetInactiveObjects()
	{
		for (auto& object : objects)
		{
			if (!object->isActive())
				return object.get();
		}
		return nullptr;
	}

	void Update(float deltaTime)
	{
		for (auto& object : objects)
			object->Update(deltaTime);
	}

	void Render(sf::RenderWindow& window)
	{
		for (auto& object : objects)
			object->Render(window);
	}
};
