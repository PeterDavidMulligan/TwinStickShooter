////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 14/03/16
///	Last Edit: 22/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include "TestScreen.h"

////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////
goo::TestScreen::TestScreen(sf::RenderWindow& window, goo::AssetManager& assets, int& currentScreen) :
goo::Screen(window, assets, currentScreen)
{
	initialise();
}

////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
///	\brief Initial class setup
///
////////////////////////////////////////////////////////////
void goo::TestScreen::initialise()
{
	/*if (!m_texture.loadFromFile("../Assets/Art/test.png"))
	{
		std::cout << "Error" << std::endl;
	}*/
	m_sprite.setTexture(m_assets.getTexture("Player"));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);
}

////////////////////////////////////////////////////////////
///	\brief Function that takes care of user input
///
/// \param e sf::Event to respond to
///
/// \param currentScreen Pointer to integer controlling
/// the current screen
///
////////////////////////////////////////////////////////////
void goo::TestScreen::input(sf::Event e)
{
	checkForScreenClose(e);
	float leftX = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X));
	float leftY = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));
	
	if (leftX > 50 || leftX < -50 || leftY > 50 || leftY < -50)
	{
		m_velocity = sf::Vector2f(leftX, leftY);
	}
	else
	{
		float friction = 0.6;
		m_velocity = sf::Vector2f(round(m_velocity.x * friction), round(m_velocity.y * friction));
	}
}

////////////////////////////////////////////////////////////
///	\brief Called once a frame
///
/// \param elapsedTime Time passed since last frame
///
////////////////////////////////////////////////////////////
void goo::TestScreen::update(sf::Time elapsedTime)
{
	float deadZone = 20;
	if (m_velocity.x < deadZone && m_velocity.x > -deadZone)
	{
		m_velocity.x = 0;
	}
	if (m_velocity.y < deadZone && m_velocity.y > -deadZone)
	{
		m_velocity.y = 0;
	}

	float rightX = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R));
	float rightY = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V));

	if (rightX > 50 || rightX < -50 || rightY > 50 || rightY < -50)
	{
		setFacing(sf::Vector2f(m_sprite.getPosition().x - rightX, m_sprite.getPosition().y - rightY));
	}
	m_sprite.move(m_velocity.x * elapsedTime.asSeconds() * m_speed, m_velocity.y * elapsedTime.asSeconds() * m_speed);
	rotateToHeading();

}

////////////////////////////////////////////////////////////
///	\brief Draws assets to the sf::Renderwindow
///
////////////////////////////////////////////////////////////
void goo::TestScreen::draw()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_sprite);
}

////////////////////////////////////////////////////////////
// Private Function
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Calculates the direction in degrees to a given
/// target and then sets the Tower's heading to that value
///
/// \param target The sf::Vector2f that you want the Tower
/// to face
///
////////////////////////////////////////////////////////////
void goo::TestScreen::setFacing(const sf::Vector2f target)
{
	//Set target offset
	sf::Vector2f offset(target.y - m_sprite.getPosition().y, target.x - m_sprite.getPosition().x);
	// This is the opposite of how normal geometry works - we must multiply the y component
	//by - 1 when doing angle calculation.
	float degrees = atan2(offset.y, offset.x) / acos(-1) * 180 + 180;
	m_heading = static_cast<int>(degrees + 90) % 360;
}

////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Rotates the tower the shortest direction to face
/// the Tower's heading value
///
////////////////////////////////////////////////////////////
void goo::TestScreen::rotateToHeading()
{
	int degrees = m_sprite.getRotation();
	if (degrees != m_heading)//If it's not looking where it should be...
	{
		int rotation = m_heading - degrees % 360;//Check how far it has left to go
		int signOfRotation = std::copysign(1.0f, rotation); //Check if that's shorter clockwise or not
		int rotationSpeed = m_rotationSpeed;	//Set rotation speed to towers speed
		if (std::abs(rotation) <= rotationSpeed)
		{
			//If the tower is leass than a turn away,
			//reduce the turn speed to stop 'flip/flop'
			rotationSpeed = 1;
		}
		if (std::abs(rotation) < 180)
		{
			m_sprite.rotate(signOfRotation * rotationSpeed);
		}
		else // degrees >= 180
		{
			m_sprite.rotate(-1.0f * signOfRotation * rotationSpeed);
		}
	}
}