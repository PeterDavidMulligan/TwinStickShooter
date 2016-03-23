////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 23/03/16
///	Last Edit: 23/03/16
////////////////////////////////////////////////////////////
#ifndef ROTATINGSPRITE_HEADER
#define ROTATINGSPRITE_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "MovingSprite.h"

////////////////////////////////////////////////////////////
///	\brief Screen subclass for running tests
///
////////////////////////////////////////////////////////////
namespace goo
{
	class RotatingSprite : public goo::MovingSprite
	{
	protected:
		////////////////////////////////////////////////////////////
		// Member Variables
		////////////////////////////////////////////////////////////
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
		RotatingSprite(goo::AssetManager& assets);
		RotatingSprite(sf::Vector2f position, goo::AssetManager& assets);
		~RotatingSprite();

		////////////////////////////////////////////////////////////
		// Public Functions
		////////////////////////////////////////////////////////////
		void update(sf::Time elapsedTime);

		////////////////////////////////////////////////////////////
		// Getter & Setter Functions
		////////////////////////////////////////////////////////////
		sf::Vector2f getPosition();
		float getRotationSpeed();
		float getHeading();
		void setPosition(sf::Vector2f position);
		void setRotationSpeed(float speed);
		void setHeading(float heading);
	};
}
#endif