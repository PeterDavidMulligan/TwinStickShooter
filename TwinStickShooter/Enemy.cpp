////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 22/03/16
///	Last Edit: 22/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include "Enemy.h"
#include "Player.h"

////////////////////////////////////////////////////////////
// Constructor/Destructor
////////////////////////////////////////////////////////////
goo::Enemy::Enemy(goo::Player& player, goo::AssetManager& assets) :
m_assets(assets), m_player(player)
{
	initialise();
}
goo::Enemy::Enemy(sf::Vector2f position, goo::Player& player, goo::AssetManager& assets) :
m_assets(assets), m_player(player)
{
	m_sprite.setPosition(position);
	initialise();
}

////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
///	\brief Initial class setup
///
////////////////////////////////////////////////////////////
void goo::Enemy::initialise()
{
	m_sprite.setTexture(m_assets.getTexture("Enemy"));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2,
		m_sprite.getLocalBounds().height / 2);
	m_speed = m_assets.getValue("EnemySpeed");
	m_velocityDeadZone = m_assets.getValue("VelocityDeadzone");
}

////////////////////////////////////////////////////////////
///	\brief Called once a frame
///
/// \param elapsedTime Time passed since last frame
///
////////////////////////////////////////////////////////////
void goo::Enemy::update(sf::Time elapsedTime)
{
	sf::Vector2f directionToPlayer(m_player.getPosition().x - m_sprite.getPosition().x,
		m_player.getPosition().y - m_sprite.getPosition().y);
	float distanceToPlayer = sqrt((directionToPlayer.x * directionToPlayer.x) + (directionToPlayer.y * directionToPlayer.y));
	if (distanceToPlayer > 1)
	{
		//The *100 is to make the player and enemy speeds be on the same scale
		m_velocity = sf::Vector2f(((directionToPlayer.x / distanceToPlayer) * 100) * m_speed * elapsedTime.asSeconds(),
			((directionToPlayer.y / distanceToPlayer) * 100) * m_speed * elapsedTime.asSeconds());

		m_sprite.move(m_velocity);
	}
	else
	{
		m_velocity = sf::Vector2f(0, 0);
	}
	
	
}

////////////////////////////////////////////////////////////
///	\brief Uses the current RenderWindow to draw elements
///
/// \param window Current RenderWindow
///
////////////////////////////////////////////////////////////
void goo::Enemy::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

////////////////////////////////////////////////////////////
// Getter Functions
////////////////////////////////////////////////////////////
sf::Vector2f goo::Enemy::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f goo::Enemy::getVelocity()
{
	return m_velocity;
}
float goo::Enemy::getSpeed()
{
	return m_speed;
}
sf::Sprite goo::Enemy::getSprite()
{
	return m_sprite;
}
sf::Vector2f goo::Enemy::getScale()
{
	return m_sprite.getScale();
}
////////////////////////////////////////////////////////////
// Setter Functions
////////////////////////////////////////////////////////////
void goo::Enemy::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}
void goo::Enemy::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}
void goo::Enemy::setSpeed(float speed)
{
	m_speed = speed;
}
void goo::Enemy::setSprite(sf::Sprite sprite)
{
	m_sprite = sprite;
}
void goo::Enemy::setScale(sf::Vector2f scale)
{
	m_sprite.setScale(scale);
}