////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 14/03/16
///	Last Edit: 20/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include "TestScreen.h"
#include <Thor\Math.hpp>
#include <Thor\Animations.hpp>

////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////
goo::TestScreen::TestScreen(sf::RenderWindow& window, goo::TextureManager& textures,
	goo::SoundManager& sounds, goo::FontManager& fonts) :
	Screen(window, textures, sounds, fonts)
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
	//This is the moveable player object thing
	m_textures.load("player", "../Assets/Art/player.png");
	m_playerSprite.setTexture(m_textures.get("player"));
	m_playerSprite.setOrigin(m_playerSprite.getLocalBounds().width / 2, m_playerSprite.getLocalBounds().height / 2);
	m_playerSprite.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);

	//Particle system
	m_particleEmitter.setEmissionRate(30);
	m_particleEmitter.setParticleLifetime(thor::Distributions::uniform(sf::seconds(1.5), sf::seconds(3.5)));
	m_particleEmitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, -35), 15.f)); // Emit towards direction with deviation of 15°
	m_particleEmitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
	
	m_particleEmitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(m_playerSprite.getPosition().x,
		m_playerSprite.getPosition().y), 25));
	m_textures.load("particle", "../Assets/Art/particle.png");
	m_particleSystem.setTexture(m_textures.get("particle"));
	m_particleEmitter.setParticleRotationSpeed(15);
	thor::FadeAnimation fader(0.05f, 0.25f);
	m_particleSystem.addAffector(thor::AnimationAffector(fader));
	m_particleSystem.addEmitter(thor::refEmitter(m_particleEmitter));
	
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
void goo::TestScreen::input(sf::Event e, int* currentScreen)
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
	  // Emit particles in given circle
	m_particleSystem.update(elapsedTime);
	//update the particle system
	m_particleEmitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(m_playerSprite.getPosition().x,
		m_playerSprite.getPosition().y), 25));

	//Move the player sprite if the vector is powerful enough
	float deadZone = 20;
	if (m_velocity.x < deadZone && m_velocity.x > -deadZone)
	{
		m_velocity.x = 0;
	}
	if (m_velocity.y < deadZone && m_velocity.y > -deadZone)
	{
		m_velocity.y = 0;
	}

	//rotate the sprite with the right stick
	float rightX = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R));
	float rightY = round(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V));
	if (rightX > 50 || rightX < -50 || rightY > 50 || rightY < -50)
	{
		setFacing(sf::Vector2f(m_playerSprite.getPosition().x - rightX, m_playerSprite.getPosition().y - rightY));
	}
	m_playerSprite.move(m_velocity.x * elapsedTime.asSeconds() * m_speed, m_velocity.y * elapsedTime.asSeconds() * m_speed);
	rotateToHeading(elapsedTime);
}

////////////////////////////////////////////////////////////
///	\brief Draws assets to the sf::Renderwindow
///
////////////////////////////////////////////////////////////
void goo::TestScreen::draw()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_particleSystem);
	m_window.draw(m_playerSprite);
	
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
	sf::Vector2f offset(target.y - m_playerSprite.getPosition().y, target.x - m_playerSprite.getPosition().x);
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
void goo::TestScreen::rotateToHeading(sf::Time elapsedTime)
{
	int degrees = m_playerSprite.getRotation();
	if (degrees != m_heading)//If it's not looking where it should be...
	{
		int rotation = m_heading - degrees % 360;//Check how far it has left to go
		int signOfRotation = std::copysign(1.0f, rotation); //Check if that's shorter clockwise or not
		int rotationSpeed = m_rotationSpeed * elapsedTime.asSeconds();	//Set rotation speed to towers speed
		if (std::abs(rotation) <= rotationSpeed)
		{
			//If the tower is leass than a turn away,
			//reduce the turn speed to stop 'flip/flop'
			rotationSpeed = 1 * elapsedTime.asSeconds();
		}
		if (std::abs(rotation) < 180)
		{
			m_playerSprite.rotate(signOfRotation * rotationSpeed);
		}
		else // degrees >= 180
		{
			m_playerSprite.rotate(-1.0f * signOfRotation * rotationSpeed);
		}
	}
}