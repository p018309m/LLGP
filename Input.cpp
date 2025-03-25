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
		BroadcastOnMoveUp(sf::Keyboard::Key::W);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		BroadcastOnMoveDown(sf::Keyboard::Key::S);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		BroadcastOnMoveLeft(sf::Keyboard::Key::A);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		BroadcastOnMoveRight(sf::Keyboard::Key::D);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		BroadcastOnShoot(sf::Mouse::Button::Left);
	}
}


void Input::BroadcastOnMoveUp(sf::Keyboard::Key key)
{
	OnMoveUp.Invoke(key);
}

void Input::BroadcastOnMoveDown(sf::Keyboard::Key key)
{
	OnMoveDown.Invoke(key);
}

void Input::BroadcastOnMoveLeft(sf::Keyboard::Key key)
{
	OnMoveLeft.Invoke(key);
}

void Input::BroadcastOnMoveRight(sf::Keyboard::Key key)
{
	OnMoveRight.Invoke(key);
}

void Input::BroadcastOnShoot(sf::Mouse::Button key)
{
	OnShoot.Invoke(key);
}
