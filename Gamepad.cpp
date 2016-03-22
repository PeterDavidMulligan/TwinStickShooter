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
////////////////////////////////////////////////////////////
///	\brief Returns a vector of length 1 in the direction
/// the stick is being pushed
///
/// \param playerID enum stating which controller is being
/// queryed
///
/// \return Returns the heading vector if successful or a
/// zero vector if it fails
///
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
////////////////////////////////////////////////////////////
///	\brief Returns a vector of length 1 in the direction
/// the stick is being pushed
///
/// \param playerID enum stating which controller is being
/// queryed
///
/// \return Returns the heading vector if successful or a
/// zero vector if it fails
///
////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////
///	\brief Returns the direction in degrees the stick is
/// being pushed
///
/// \param playerID enum stating which controller is being
/// queryed
///
/// \return Returns the degrees if successful and 0 if not
///
////////////////////////////////////////////////////////////
float goo::Gamepad::rightStickDegrees(goo::ControllerID playerID)
{
	int player = static_cast<int>(playerID);
	if (sf::Joystick::isConnected(player))
	{
		float x = sf::Joystick::getAxisPosition(player, sf::Joystick::Axis::X);
		float y = sf::Joystick::getAxisPosition(player, sf::Joystick::Axis::Y);
		return atan(y/x);
	}
	return 0;
}
////////////////////////////////////////////////////////////
///	\brief Returns the direction in degrees the stick is
/// being pushed
///
/// \param playerID enum stating which controller is being
/// queryed
///
/// \return Returns the degrees if successful and 0 if not
///
////////////////////////////////////////////////////////////
float goo::Gamepad::leftStickDegrees(goo::ControllerID playerID)
{
	if (sf::Joystick::isConnected(0))
	{
		float x = sf::Joystick::Axis::R;
		float y = sf::Joystick::Axis::U;
		return atan(y/x);
	}
	return 0;
}
////////////////////////////////////////////////////////////
///	\brief Returns the direction in radians the stick is
/// being pushed
///
/// \param playerID enum stating which controller is being
/// queryed
///
/// \return Returns the radians if successful and 0 if not
///
////////////////////////////////////////////////////////////
float goo::Gamepad::rightStickRadians(goo::ControllerID playerID)
{
	int player = static_cast<int>(playerID);
	if (sf::Joystick::isConnected(player))
	{
		float x = sf::Joystick::getAxisPosition(player, sf::Joystick::Axis::X);
		float y = sf::Joystick::getAxisPosition(player, sf::Joystick::Axis::Y);
		return atan(y / x);
	}
	return 0;
}
////////////////////////////////////////////////////////////
///	\brief Returns the direction in radians the stick is
/// being pushed
///
/// \param playerID enum stating which controller is being
/// queryed
///
/// \return Returns the radians if successful and 0 if not
///
////////////////////////////////////////////////////////////
float goo::Gamepad::leftStickRadians(goo::ControllerID playerID)
{
	if (sf::Joystick::isConnected(0))
	{
		float x = sf::Joystick::Axis::R;
		float y = sf::Joystick::Axis::U;
		float degs = atan(y / x);
		return degreesToRadians(degs);
	}
	return 0;
}
////////////////////////////////////////////////////////////
///	\brief Converts degrees to radians
///
/// \param degrees The value in degrees
///
/// \return Returns the value in radians
///
////////////////////////////////////////////////////////////
float goo::Gamepad::degreesToRadians(float degrees)
{
	float radians = degrees * (M_PI / 180);
	return radians;
}
////////////////////////////////////////////////////////////
///	\brief Converts radians to degrees
///
/// \param degrees The value in radians
///
/// \return Returns the value in degrees
///
////////////////////////////////////////////////////////////
float goo::Gamepad::radiansToDegrees(float radians)
{
	float degrees = radians * (180 / M_PI);
	return degrees;
}