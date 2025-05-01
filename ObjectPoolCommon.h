#pragma once
#include "SFML/Graphics.hpp"

template<typename T>
class ObjectPoolCommon
{
private:
	std::vector<std::unique_ptr<T>> objects;

public:
	ObjectPoolCommon(int size)
	{
		objects.reserve(size);
		for (int i = 0; i < size; ++i)
			objects.push_back(std::make_unique<T>());
	}

	std::vector<std::unique_ptr<T>>& GetAllObjects()
	{
		return objects;
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
