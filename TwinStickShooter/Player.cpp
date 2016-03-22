////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 22/03/16
///	Last Edit: 22/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include "Player.h"

////////////////////////////////////////////////////////////
// Constructor/Destructor
////////////////////////////////////////////////////////////
goo::Player::Player(){}
goo::Player::Player(goo::AssetManager& assets)
{
	m_sprite.setTexture(assets.getTexture("Player"));
	initialise();
}
goo::Player::Player(sf::Vector2f position, goo::AssetManager& assets)
{
	m_sprite.setTexture(assets.getTexture("Player"));
	m_sprite.setPosition(position);
	initialise();
}
goo::Player::~Player()
{

}


////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
///	\brief Initial class setup
///
////////////////////////////////////////////////////////////
void goo::Player::initialise()
{
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2,
		m_sprite.getLocalBounds().height / 2);
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
void goo::Player::input(sf::Event e)
{
	float leftX = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X));
	float leftY = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));

	if (leftX > 50 || leftX < -50 || leftY > 50 || leftY < -50)
	{
		m_velocity = sf::Vector2f(leftX, leftY);
	}
	else
	{
		m_velocity = sf::Vector2f(round(m_velocity.x * m_friction), round(m_velocity.y * m_friction));
	}
}

////////////////////////////////////////////////////////////
///	\brief Called once a frame
///
/// \param elapsedTime Time passed since last frame
///
////////////////////////////////////////////////////////////
void goo::Player::update(sf::Time elapsedTime)
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
void goo::Player::draw(sf::RenderWindow& window)
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
void goo::Player::setFacing(const sf::Vector2f target)
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
void goo::Player::rotateToHeading()
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
sf::Vector2f goo::Player::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f goo::Player::getVelocity()
{
	return m_velocity;
}
float goo::Player::getSpeed()
{
	return m_speed;
}
float goo::Player::getRotationSpeed()
{
	return m_rotationSpeed;
}
float goo::Player::getHeading()
{
	return m_heading;
}
float goo::Player::getFriction()
{
	return m_friction;
}
////////////////////////////////////////////////////////////
// Setter Functions
////////////////////////////////////////////////////////////
void goo::Player::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}
void goo::Player::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}
void goo::Player::setSpeed(float speed)
{
	m_speed = speed;
}
void goo::Player::setRotationSpeed(float speed)
{
	m_rotationSpeed = speed;
}
void goo::Player::setFriction(float friction)
{
	m_friction = friction;
}