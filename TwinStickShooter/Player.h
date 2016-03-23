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
#include "RotatingSprite.h"
#include "..\Gamepad.h"

////////////////////////////////////////////////////////////
///	\brief Screen subclass for running tests
///
////////////////////////////////////////////////////////////
namespace goo
{
	class Player : public goo::RotatingSprite
	{
	private:
		////////////////////////////////////////////////////////////
		// Member Variables
		////////////////////////////////////////////////////////////
		int m_analogDeadzone;

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
		void update(sf::Time elapsedTime);
	};
}
#endif