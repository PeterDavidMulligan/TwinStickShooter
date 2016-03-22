////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 21/03/16
////////////////////////////////////////////////////////////
#ifndef ASSETMANAGER_HEADER
#define ASSETMANAGER_HEADER
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "TextureManager.h"
#include "SoundManager.h"
#include "FontManager.h"

namespace goo
{
	////////////////////////////////////////////////////////////
	///	\brief A class that acts as a gateway to the multiple
	/// asset manager classes
	///
	////////////////////////////////////////////////////////////
	class AssetManager
	{
	private:
		goo::TextureManager m_textures;
		goo::SoundManager m_sounds;
		goo::FontManager m_fonts;
	public:
		sf::Texture& getTexture(std::string id);
		sf::SoundBuffer& getSoundBuffer(std::string id);
		sf::Font& getFont(std::string id);
	};
}
#endif
////////////////////////////////////////////////////////////
///	\class This class is just a wrapper for the asset
/// management classes so they can be passed as a single
/// parameter
///
////////////////////////////////////////////////////////////