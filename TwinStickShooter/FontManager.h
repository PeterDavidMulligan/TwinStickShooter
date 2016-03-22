////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 21/03/16
////////////////////////////////////////////////////////////
#ifndef FONTMANAGER_HEADER
#define FONTMANAGER_HEADER
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <memory>
#include "AssetLoader.h"

namespace goo
{
	////////////////////////////////////////////////////////////
	///	\brief A class that acts as a singular repository for
	/// font assets
	///
	////////////////////////////////////////////////////////////
	class FontManager : AssetLoader
	{
	private:
		std::map<std::string,	//key
			std::unique_ptr<sf::Font >> m_fontMap;	//value
		void loadFonts(bool debug = false);
	public:
		FontManager();
		~FontManager();
		void load(std::string id, const std::string path);
		sf::Font& get(std::string id);
		const sf::Font& get(std::string id) const;
	};
}
////////////////////////////////////////////////////////////
///	\class A class that acts as a singular repository for
/// font assets. It loads a JSON and creates a map fom the
/// list of unique ids and strings of paths that are listed
/// in the file
///
////////////////////////////////////////////////////////////
#endif
