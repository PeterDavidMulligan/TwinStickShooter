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
goo::RotatingSprite(assets)
{
	initialise();
}
goo::Player::Player(sf::Vector2f position, goo::AssetManager& assets) :
goo::RotatingSprite(assets)
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
	goo::RotatingSprite::update(elapsedTime);
}