////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 14/03/16
///	Last Edit: 14/03/16
////////////////////////////////////////////////////////////
#ifndef SCREEN_HEADER
#define SCREEN_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include "TwinStickShooter\TextureManager.h"
#include "TwinStickShooter\SoundManager.h"
#include "TwinStickShooter\FontManager.h"

namespace goo
{
	////////////////////////////////////////////////////////////
	///	\brief ABC for Screen subclasses
	///
	////////////////////////////////////////////////////////////
	class Screen
	{
	protected:
		////////////////////////////////////////////////////////////
		// Protected Variables
		////////////////////////////////////////////////////////////
		sf::RenderWindow& m_window;
		goo::TextureManager& m_textures;
		goo::SoundManager& m_sounds;
		goo::FontManager& m_fonts;
		
		////////////////////////////////////////////////////////////
		// Protected Functions
		////////////////////////////////////////////////////////////
		void checkForScreenClose(sf::Event e);
	public:
		////////////////////////////////////////////////////////////
		// Constructor
		////////////////////////////////////////////////////////////
		Screen(sf::RenderWindow& window, goo::TextureManager& textures,
			goo::SoundManager& m_sounds, goo::FontManager& fonts);

		////////////////////////////////////////////////////////////
		// Public Virtual Functions
		////////////////////////////////////////////////////////////
		virtual void initialise() = 0;
		virtual void input(sf::Event e, int* currentScreen) = 0;
		virtual void update(sf::Time elapsedTime) = 0;
		virtual void draw() = 0;
	};
}
#endif

////////////////////////////////////////////////////////////
///	\class goo::Screen
///
/// Screen is an abstract class that acts as a self
/// contained drawable screen. Every Screen has a reference
/// to the currentScreen integer stored in main. Changing
/// it will change the active screen.
///
////////////////////////////////////////////////////////////