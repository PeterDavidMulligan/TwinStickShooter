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
goo::Player::Player(goo::AssetManager& assets) :
m_assets(assets)
{
	initialise();
}
goo::Player::Player(sf::Vector2f position, goo::AssetManager& assets) :
m_assets(assets)
{
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
	m_sprite.setTexture(m_assets.getTexture("Player"));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2,
		m_sprite.getLocalBounds().height / 2);
	m_speed = m_assets.getValue("PlayerSpeed");
	m_rotationSpeed = m_assets.getValue("PlayerRotationSpeed");
	m_heading = 0;
	m_speedModifier = m_assets.getValue("PlayerSpeedMod");
	m_velocityDeadZone = m_assets.getValue("VelocityDeadzone");
	m_analogDeadzone = m_assets.getValue("AnalogDeadzone");
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
void goo::Player::input()
{
	float leftX = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X));
	float leftY = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));

	if (leftX > m_analogDeadzone || leftX < -m_analogDeadzone ||
		leftY > m_analogDeadzone || leftY < -m_analogDeadzone)
	{
		m_velocity = sf::Vector2f(leftX, leftY);
	}
	else
	{
		m_velocity = sf::Vector2f(0, 0);
	}

	float rightX = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R));
	float rightY = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V));

	if (rightX > m_analogDeadzone || rightX < -m_analogDeadzone ||
		rightY > m_analogDeadzone || rightY < -m_analogDeadzone)
	{
		setFacing(sf::Vector2f(m_sprite.getPosition().x - rightX,
			m_sprite.getPosition().y - rightY));
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
	input();

	//Check the velocity is powerful enough to move the sprite
	if ((m_velocity.x < m_velocityDeadZone && m_velocity.x > -m_velocityDeadZone) &&
		(m_velocity.y < m_velocityDeadZone && m_velocity.y > -m_velocityDeadZone))
	{
		m_velocity = sf::Vector2f(0, 0);
	}
	//move the sprite
	m_sprite.move(m_velocity.x * m_speed * m_speedModifier * elapsedTime.asSeconds(),
		m_velocity.y * m_speed * m_speedModifier * elapsedTime.asSeconds());

	rotateToHeading();
}

////////////////////////////////////////////////////////////
///	\brief Uses the current RenderWindow to draw elements
///
/// \param window Current RenderWindow
///
////////////////////////////////////////////////////////////
void goo::Player::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);

}

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
float goo::Player::getRotationSpeed()
{
	return m_rotationSpeed;
}
float goo::Player::getHeading()
{
	return m_heading;
}
sf::Vector2f goo::Player::getVelocity()
{
	return m_velocity;
}
float goo::Player::getSpeed()
{
	return m_speed;
}
float goo::Player::getFriction()
{
	return m_speedModifier;
}
////////////////////////////////////////////////////////////
// Setter Functions
////////////////////////////////////////////////////////////
void goo::Player::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}
void goo::Player::setRotationSpeed(float speed)
{
	m_rotationSpeed = speed;
}
void goo::Player::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}
void goo::Player::setSpeed(float speed)
{
	m_speed = speed;
}
void goo::Player::setFriction(float friction)
{
	m_speedModifier = friction;
}