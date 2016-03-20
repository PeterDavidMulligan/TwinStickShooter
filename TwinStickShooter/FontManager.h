////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 20/03/16
////////////////////////////////////////////////////////////

#ifndef FONTMANAGER_HEADER
#define FONTMANAGER_HEADER

////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 01/03/16
///	Last Edit: 10/03/16
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <memory>

namespace goo
{
	class FontManager
	{
	private:
		std::map<std::string,
			std::unique_ptr<sf::Font >> m_fontMap;
	public:
		FontManager();
		void load(std::string id, const std::string path);
		sf::Font& get(std::string id);
		const sf::Font& get(std::string id) const;
	};
}

#endif
