////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 21/03/16
////////////////////////////////////////////////////////////
#ifndef SOUNDMANAGER_HEADER
#define SOUNDMANAGER_HEADER
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Audio.hpp>
#include <memory>
#include <map>
#include "AssetLoader.h"

namespace goo
{
	////////////////////////////////////////////////////////////
	///	\brief A class that acts as a singular repository for
	/// sound assets. 
	///
	////////////////////////////////////////////////////////////
	class SoundManager : AssetLoader
	{
	private:
		std::map<std::string,	//key
			std::unique_ptr<sf::SoundBuffer >> m_soundMap;	//value
		void loadSounds(bool debug = false);
	public:
		SoundManager();
		~SoundManager();
		void load(std::string id, const std::string path);
		sf::SoundBuffer& get(std::string id);
		const sf::SoundBuffer& get(std::string id) const;
	};
}
////////////////////////////////////////////////////////////
///	\class A class that acts as a singular repository for
/// sound assets. It loads a JSON and creates a map fom the
/// list of unique ids and strings of paths that are listed
/// in the file
///
////////////////////////////////////////////////////////////
#endif
