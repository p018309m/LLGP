#include "Input.h"

Input::Input()
{

}

Input::~Input()
{

}

void Input::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		BroadcastOnMoveUp((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) ? 1 : 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		BroadcastOnMoveDown((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) ? 1 : 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		BroadcastOnMoveLeft((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) ? 1 : 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		BroadcastOnMoveRight((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) ? 1 : 0);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		BroadcastOnShoot((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) ? 1 : 0);
	}
}


void Input::BroadcastOnMoveUp(int val)
{
	OnMoveUp.Invoke(val);
}

void Input::BroadcastOnMoveDown(int val)
{
	OnMoveDown.Invoke(val);
}

void Input::BroadcastOnMoveLeft(int val)
{
	OnMoveLeft.Invoke(val);
}

void Input::BroadcastOnMoveRight(int val)
{
	OnMoveRight.Invoke(val);
}

void Input::BroadcastOnShoot(int val)
{
	OnShoot.Invoke(val);
}
