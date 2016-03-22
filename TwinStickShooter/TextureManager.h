////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 21/03/16
////////////////////////////////////////////////////////////

#ifndef TEXTUREMANAGER_HEADER
#define TEXTUREMANAGER_HEADER

#include <SFML\Graphics.hpp>
#include "AssetLoader.h"
#include <memory>

namespace goo
{
	////////////////////////////////////////////////////////////
	///	\brief A class that acts as a singular repository for
	/// texture assets
	///
	////////////////////////////////////////////////////////////
	class TextureManager : AssetLoader
	{
	private:
		std::map<std::string,
			std::unique_ptr<sf::Texture>> m_textureMap;
		void loadTextures(bool debug = false);
		
	public:
		TextureManager();
		~TextureManager();
		void load(std::string id, const std::string path);
		sf::Texture& get(std::string id);
		const sf::Texture& get(std::string id) const;
	};
}
////////////////////////////////////////////////////////////
///	\class A class that acts as a singular repository for
/// texture assets. It loads a JSON and creates a map fom the
/// list of unique ids and strings of paths that are listed
/// in the file
///
////////////////////////////////////////////////////////////
#endif
