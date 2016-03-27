////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 22/03/16
///	Last Edit: 22/03/16
////////////////////////////////////////////////////////////
#ifndef PLAYER_HEADER
#define PLAYER_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "AssetManager.h"
#include "..\Gamepad.h"

////////////////////////////////////////////////////////////
///	\brief Screen subclass for running tests
///
////////////////////////////////////////////////////////////
namespace goo
{
	class Player
	{
	private:
		////////////////////////////////////////////////////////////
		// Member Variables
		////////////////////////////////////////////////////////////
		int m_analogDeadzone;
		goo::AssetManager& m_assets;
		sf::Sprite m_sprite;
		sf::Vector2f m_velocity;
		float m_velocityDeadZone;
		float m_speed;
		float m_speedModifier;

		float m_rotationSpeed;
		float m_heading;

		////////////////////////////////////////////////////////////
		// Private Functions
		////////////////////////////////////////////////////////////
		void setFacing(const sf::Vector2f target);
		void rotateToHeading();

	public:
		////////////////////////////////////////////////////////////
		// Constructor/Destructor
		////////////////////////////////////////////////////////////
		Player(goo::AssetManager& assets);
		Player(sf::Vector2f position, goo::AssetManager& assets);
		~Player();

		////////////////////////////////////////////////////////////
		// Public Functions
		////////////////////////////////////////////////////////////
		void initialise();
		void input();
		void draw(sf::RenderWindow& window);
		void update(sf::Time elapsedTime);

		sf::Vector2f getVelocity();
		float getSpeed();
		float getFriction();

		void setVelocity(sf::Vector2f velocity);
		void setSpeed(float speed);
		void setFriction(float friction);

		sf::Vector2f getPosition();
		float getRotationSpeed();
		float getHeading();
		void setPosition(sf::Vector2f position);
		void setRotationSpeed(float speed);
		void setHeading(float heading);
	};
}
#endif