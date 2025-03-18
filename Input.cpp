#include "Input.h"

Input::Input()
{

}

Input::~Input()
{

}

void Input::HandleInput(std::optional<sf::Event> gameEvent, sf::RenderWindow& window)
{
	if (const auto* keyPressed = gameEvent->getIf<sf::Event::KeyPressed>())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			BroadcastOnMoveUp(1);
		}
	}
}


void Input::BroadcastOnMoveUp(int arg1)
{
	OnMoveUp.Invoke(arg1);
}
