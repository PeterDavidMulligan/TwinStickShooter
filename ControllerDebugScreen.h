////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 19/03/16
///	Last Edit: 19/03/16
////////////////////////////////////////////////////////////
#ifndef CONTROLLERDEBUGSCREEN_HEADER
#define CONTROLLERDEBUGSCREEN_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Gamepad.h"
#include "Screen.h"
#include "TwinStickShooter\SoundManager.h"
#include "TwinStickShooter\FontManager.h"

////////////////////////////////////////////////////////////
///	\brief Screen subclass for mapping and debugging a
/// game controller
///
////////////////////////////////////////////////////////////
namespace goo
{
	class ControllerDebugScreen : public goo::Screen
	{
	private:
		////////////////////////////////////////////////////////////
		// Member Variables
		////////////////////////////////////////////////////////////
		int m_displayedController = 0;
		sf::Text *m_buttonTexts;	//Array
		sf::Font m_font;

		////////////////////////////////////////////////////////////
		// Public Functions
		////////////////////////////////////////////////////////////
		void changeDisplayedConroller(goo::ControllerID displayedController);
	public:
		////////////////////////////////////////////////////////////
		// Constructor
		////////////////////////////////////////////////////////////
		ControllerDebugScreen(sf::RenderWindow& window, goo::TextureManager& textures,
			goo::SoundManager& sounds, goo::FontManager& fonts);
		////////////////////////////////////////////////////////////
		// Destructor
		////////////////////////////////////////////////////////////
		~ControllerDebugScreen();
		////////////////////////////////////////////////////////////
		// Public Functions
		////////////////////////////////////////////////////////////
		void initialise();
		void input(sf::Event e, int* currentScreen);
		void update(sf::Time elapsedTime);
		void draw();
	};
}
#endif
////////////////////////////////////////////////////////////
///	\class goo::ControllerDebugScreen
///
/// Subclass of Screen. This is just a Screen for testing
/// controller input. It displayes a numbered string for
/// each of the buttons on a pc controller and outputs
/// their values. Useful for input debugging and button
/// mapping
///
////////////////////////////////////////////////////////////