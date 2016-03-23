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
RotatingSprite(assets)
{
	initialise();
}
goo::Player::Player(sf::Vector2f position, goo::AssetManager& assets) :
RotatingSprite(assets)
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
	m_friction = m_assets.getValue("PlayerFriction");
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
// Getter Functions
////////////////////////////////////////////////////////////
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
	return m_friction;
}
////////////////////////////////////////////////////////////
// Setter Functions
////////////////////////////////////////////////////////////
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
	m_friction = friction;
}