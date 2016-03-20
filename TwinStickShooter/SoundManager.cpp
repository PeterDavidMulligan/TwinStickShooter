////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 20/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SoundManager.h"
#include <SFML\Audio.hpp>
#include <assert.h>

////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////
goo::SoundManager::SoundManager()
{

}

////////////////////////////////////////////////////////////
///	\brief Loads a sound from file @param path into the
/// games central sound repo
///
/// \param id Unique id used to refer to sound
///
/// \param path Relative path to sound
///
////////////////////////////////////////////////////////////
void goo::SoundManager::load(std::string id, const std::string path)
{
	//Create a pointer to a sound created on the heap
	std::unique_ptr<sf::SoundBuffer> sound(new sf::SoundBuffer());
	//load the sound
	sound->loadFromFile(path);
	//insert() returns a pair<int,bool>. The int is it's iteration in the map
	//The bool is whether there was an id collision/successful insertion so we
	//store it and then assert it (insert a breakpoint if !boolean) and print
	//an error message if false
	auto inserted = m_soundMap.insert(std::make_pair(id, std::move(sound)));//move so the original is in the map
	assert(inserted.second,
		"SoundManager::load : Failed to load (" + id + ") @ " + path + ". Possible id collision.");
}

////////////////////////////////////////////////////////////
///	\brief Used to retrieve sound from repo using it's
/// unique id
///
/// \param id Unique id used to refer to sound
///
////////////////////////////////////////////////////////////
sf::SoundBuffer& goo::SoundManager::get(std::string id)
{
	auto sound = m_soundMap.find(id);
	return *sound->second;
}

////////////////////////////////////////////////////////////
///	\brief Used to retrieve sound from repo using it's
/// unique id. This overload is used for refs and ptrs to
/// const SoundManagers
///
/// \param id Unique id used to refer to sound
///
////////////////////////////////////////////////////////////
const sf::SoundBuffer& goo::SoundManager::get(std::string id) const
{
	auto sound = m_soundMap.find(id);
	return *sound->second;
}