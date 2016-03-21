////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 14/03/16
///	Last Edit: 14/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Screen.h"

////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////
goo::Screen::Screen(sf::RenderWindow& window, goo::TextureManager& textures,
	goo::SoundManager& sounds, goo::FontManager& fonts) :
m_window(window), m_textures (textures), m_sounds(sounds), m_fonts(fonts){}

////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
///	\brief This function is to be called in all Screen
/// subclass's input function. It just checks if the user
/// has pressed the X in the top-right corner of a window
///
/// \param e This is the event passed in to a Screen's
/// update function
///
////////////////////////////////////////////////////////////
void goo::Screen::checkForScreenClose(sf::Event e)
{
	if (e.type == sf::Event::Closed)
	{
		m_window.close();
	}
}