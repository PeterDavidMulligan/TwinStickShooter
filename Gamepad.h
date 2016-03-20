////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 14/03/16
///	Last Edit: 14/03/16
////////////////////////////////////////////////////////////
#ifndef GAMEPAD_HEADER
#define GAMEPAD_HEADER
#define _USE_MATH_DEFINES
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML\Graphics.hpp"
#include <SFML\Window\Joystick.hpp>
#include <math.h>

namespace goo
{
	////////////////////////////////////////////////////////////
	///	\brief Enum to query specific gamepads
	///
	////////////////////////////////////////////////////////////
	enum ControllerID
	{
		Player1,
		Player2
	};
	////////////////////////////////////////////////////////////
	///	\brief Class for querying the gamepad state with static
	///	functions
	///
	////////////////////////////////////////////////////////////
	class Gamepad
	{
	public:
		////////////////////////////////////////////////////////////
		// Public Static Functions
		////////////////////////////////////////////////////////////
		static sf::Vector2f rightStickHeadingVector(goo::ControllerID player);
		static sf::Vector2f leftStickHeadingVector(goo::ControllerID player);
		static float degreesToRadians(float degrees);
		static float radiansToDegrees(float radians);
	};
}
#endif
////////////////////////////////////////////////////////////
///	\class goo::Gamepad
///
///	Gamepad is a class of static functions to query the
/// current state of the gamepad. It has functions that return
/// whether buttons are pressed, as well as the degree and
/// heading vector of the analogue sticks
///
////////////////////////////////////////////////////////////