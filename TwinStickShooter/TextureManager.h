////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 20/03/16
////////////////////////////////////////////////////////////

#ifndef TEXTUREMANAGER_HEADER
#define TEXTUREMANAGER_HEADER

////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 01/03/16
///	Last Edit: 10/03/16
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <memory>

namespace goo
{
	class TextureManager
	{
	private:
		std::map<std::string,
			std::unique_ptr<sf::Texture>> m_textureMap;
	public:
		TextureManager();
		void load(std::string id, const std::string path);
		sf::Texture& get(std::string id);
		const sf::Texture& get(std::string id) const;
	};
}

#endif // !TEXTUREMANAGER_HEADER
