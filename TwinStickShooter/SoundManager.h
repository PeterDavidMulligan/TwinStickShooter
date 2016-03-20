////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 20/03/16
////////////////////////////////////////////////////////////

#ifndef SOUNDMANAGER_HEADER
#define SOUNDMANAGER_HEADER

////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 01/03/16
///	Last Edit: 10/03/16
////////////////////////////////////////////////////////////
#include <SFML\Audio.hpp>
#include <memory>
#include <map>

namespace goo
{
	class SoundManager
	{
	private:
		std::map<std::string,
			std::unique_ptr<sf::SoundBuffer >> m_soundMap;
	public:
		SoundManager();
		void load(std::string id, const std::string path);
		sf::SoundBuffer& get(std::string id);
		const sf::SoundBuffer& get(std::string id) const;
	};
}

#endif
