////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 14/03/16
///	Last Edit: 14/03/16
////////////////////////////////////////////////////////////
#ifndef TESTSCREEN_HEADER
#define TESTSCREEN_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Gamepad.h"
#include "Screen.h"
#include "TwinStickShooter\Player.h"

////////////////////////////////////////////////////////////
///	\brief Screen subclass for running tests
///
////////////////////////////////////////////////////////////
namespace goo
{
	class TestScreen : public goo::Screen
	{
	public:
		////////////////////////////////////////////////////////////
		// Constructor
		////////////////////////////////////////////////////////////
		TestScreen(sf::RenderWindow& window, goo::AssetManager& assets, int& currentScreen);
		~TestScreen();
		////////////////////////////////////////////////////////////
		// Member Variables
		////////////////////////////////////////////////////////////
		sf::Text m_velocityText;
		goo::Player* m_player;

		////////////////////////////////////////////////////////////
		// Public Functions
		////////////////////////////////////////////////////////////
		void initialise();
		void input(sf::Event e);
		void update(sf::Time elapsedTime);
		void draw();
	};
}
#endif
////////////////////////////////////////////////////////////
///	\class goo::TestScreen
///
/// Subclass of Screen. This is just a Screen for testing
/// and displaying works in progress
///
////////////////////////////////////////////////////////////