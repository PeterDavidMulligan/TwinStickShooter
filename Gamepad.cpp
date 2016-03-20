////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 14/03/16
///	Last Edit: 14/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Gamepad.h"
#include <iostream>

////////////////////////////////////////////////////////////
// Public Static Functions
////////////////////////////////////////////////////////////
sf::Vector2f goo::Gamepad::rightStickHeadingVector(goo::ControllerID playerID)
{
	int player = static_cast<int>(playerID);
	if (sf::Joystick::isConnected(player))
	{
		float x = sf::Joystick::getAxisPosition(player, sf::Joystick::Axis::X);
		float y = sf::Joystick::getAxisPosition(player, sf::Joystick::Axis::Y);
		return sf::Vector2f(cos(x), sin(y));
	}
	return sf::Vector2f();
}

sf::Vector2f goo::Gamepad::leftStickHeadingVector(goo::ControllerID playerID)
{
	if (sf::Joystick::isConnected(0))
	{
		float x = sf::Joystick::Axis::R;
		float y = sf::Joystick::Axis::U;
		return sf::Vector2f(cos(x), sin(y));
	}
	return sf::Vector2f();
}

float goo::Gamepad::degreesToRadians(float degrees)
{
	float radians = degrees * (M_PI / 180);
	return radians;
}

float goo::Gamepad::radiansToDegrees(float radians)
{
	float degrees = radians * (180 / M_PI);
	return degrees;
}