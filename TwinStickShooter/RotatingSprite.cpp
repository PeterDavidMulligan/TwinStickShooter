////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 22/03/16
///	Last Edit: 22/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include "RotatingSprite.h"

////////////////////////////////////////////////////////////
// Constructor/Destructor
////////////////////////////////////////////////////////////
goo::RotatingSprite::RotatingSprite(goo::AssetManager& assets) :
m_assets(assets)
{

}
goo::RotatingSprite::RotatingSprite(sf::Vector2f position, goo::AssetManager& assets) :
m_assets(assets)
{
	m_sprite.setPosition(position);
}
goo::RotatingSprite::~RotatingSprite()
{

}


////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
///	\brief Called once a frame
///
/// \param elapsedTime Time passed since last frame
///
////////////////////////////////////////////////////////////
void goo::RotatingSprite::update(sf::Time elapsedTime)
{
	float rightX = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R));
	float rightY = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V));

	if (rightX > 50 || rightX < -50 || rightY > 50 || rightY < -50)
	{
		setFacing(sf::Vector2f(m_sprite.getPosition().x - rightX, m_sprite.getPosition().y - rightY));
	}
	rotateToHeading();
}

////////////////////////////////////////////////////////////
///	\brief Draws assets to the sf::Renderwindow
///
////////////////////////////////////////////////////////////
void goo::RotatingSprite::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Calculates the direction in degrees to a given
/// target and then sets the Tower's heading to that value
///
/// \param target The sf::Vector2f that you want the Tower
/// to face
///
////////////////////////////////////////////////////////////
void goo::RotatingSprite::setFacing(const sf::Vector2f target)
{
	//Set target offset
	sf::Vector2f offset(target.y - m_sprite.getPosition().y, target.x - m_sprite.getPosition().x);
	// This is the opposite of how normal geometry works - we must multiply the y component
	//by - 1 when doing angle calculation.
	float degrees = atan2(offset.y, offset.x) / acos(-1) * 180 + 180;
	m_heading = static_cast<int>(degrees + 90) % 360;
}


////////////////////////////////////////////////////////////
/// \brief Rotates the tower the shortest direction to face
/// the Tower's heading value
///
////////////////////////////////////////////////////////////
void goo::RotatingSprite::rotateToHeading()
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

////////////////////////////////////////////////////////////
// Getter Functions
////////////////////////////////////////////////////////////
sf::Vector2f goo::RotatingSprite::getPosition()
{
	return m_sprite.getPosition();
}
float goo::RotatingSprite::getRotationSpeed()
{
	return m_rotationSpeed;
}
float goo::RotatingSprite::getHeading()
{
	return m_heading;
}
////////////////////////////////////////////////////////////
// Setter Functions
////////////////////////////////////////////////////////////
void goo::RotatingSprite::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}
void goo::RotatingSprite::setRotationSpeed(float speed)
{
	m_rotationSpeed = speed;
}