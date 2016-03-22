////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 21/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SoundManager.h"
#include <SFML\Audio.hpp>
#include <assert.h>
#include <iostream>

////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////
goo::SoundManager::SoundManager()
{
	loadSounds();
}
////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////
goo::SoundManager::~SoundManager()
{
	delete[] m_names;
	delete[] m_paths;
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

////////////////////////////////////////////////////////////
///	\brief Loads all the sounds listed in the JSON file
/// "AssetPaths.json"
///
///	\param debug (optional) Prints how many sounds are in the
/// map before and after load to console
///
////////////////////////////////////////////////////////////
void goo::SoundManager::loadSounds(bool debug)
{
	if (debug)
	{
		std::cout << "Sounds before load : " << m_soundMap.size() << std::endl;
	}
	//Store json file in JSONValue m_root
	readJSONFile("AssetPaths.json");
	//check how many elements are under the 'Textures' heading
	int elements = m_root["Assets"]["Textures"].size();
	//Allocate space on the heap for 2 string arrays of size 'elements'
	m_names = new std::string[elements];
	m_paths = new std::string[elements];
	//Loop through elements to store their values
	//When loading for sounds, for some reason it tries
	//to load an extra sound with an empty string. -1 from
	//elements to eliminate this
	for (int i = 0; i < elements - 1; i++)
	{
		m_names[i] = m_root["Assets"]["Sounds"][i]["Name"].asString().c_str();
		m_paths[i] = m_root["Assets"]["Sounds"][i]["Path"].asString().c_str();
		load(m_names[i], m_paths[i]);
	}
	if (debug)
	{
		std::cout << "Sounds after load : " << m_soundMap.size() << std::endl;
	}
}