////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 22/03/16
///	Last Edit: 22/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include "MovingSprite.h"

////////////////////////////////////////////////////////////
// Constructor/Destructor
////////////////////////////////////////////////////////////
goo::MovingSprite::MovingSprite(goo::AssetManager& assets) :
m_assets(assets)
{
	
}
goo::MovingSprite::MovingSprite(sf::Vector2f position, goo::AssetManager& assets) :
m_assets(assets)
{
	m_sprite.setPosition(position);
}
goo::MovingSprite::~MovingSprite()
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
void goo::MovingSprite::update(sf::Time elapsedTime)
{
	//Check the velocity is powerful enough to move the sprite
	if ((m_velocity.x < m_velocityDeadZone && m_velocity.x > -m_velocityDeadZone) &&
		(m_velocity.y < m_velocityDeadZone && m_velocity.y > -m_velocityDeadZone))
	{
		m_velocity = sf::Vector2f(0,0);
	}
	//move the sprite
	m_sprite.move(m_velocity.x * m_speed * m_speedModifier * elapsedTime.asSeconds(),
		m_velocity.y * m_speed * m_speedModifier * elapsedTime.asSeconds());
}

////////////////////////////////////////////////////////////
///	\brief Draws assets to the sf::Renderwindow
///
////////////////////////////////////////////////////////////
void goo::MovingSprite::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

////////////////////////////////////////////////////////////
// Getter Functions
////////////////////////////////////////////////////////////
sf::Vector2f goo::MovingSprite::getVelocity()
{
	return m_velocity;
}
float goo::MovingSprite::getSpeed()
{
	return m_speed;
}
float goo::MovingSprite::getFriction()
{
	return m_speedModifier;
}
////////////////////////////////////////////////////////////
// Setter Functions
////////////////////////////////////////////////////////////
void goo::MovingSprite::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}
void goo::MovingSprite::setSpeed(float speed)
{
	m_speed = speed;
}
void goo::MovingSprite::setFriction(float friction)
{
	m_speedModifier = friction;
}