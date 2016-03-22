////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 21/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "TextureManager.h"
#include <assert.h>
#include <iostream>
#include <fstream>

////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////
goo::TextureManager::TextureManager()
{
	loadTextures();
}
////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////
goo::TextureManager::~TextureManager()
{
	delete[] m_names;
	delete[] m_paths;
}


////////////////////////////////////////////////////////////
///	\brief Loads a texture from file @param path into the
/// games central texture repo
///
/// \param id Unique id used to refer to texture
///
/// \param path Relative path to texture
///
////////////////////////////////////////////////////////////
void goo::TextureManager::load(std::string id, const std::string path)
{
	//Create a pointer to a texture created on the heap
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	//load the texture
	texture->loadFromFile(path);
	//insert() returns a pair<int,bool>. The int is it's iteration in the map
	//The bool is whether there was an id collision/successful insertion so we
	//store it and then assert it (insert a breakpoint if !boolean) and print
	//an error message if false
	auto inserted = m_textureMap.insert(std::make_pair(id, std::move(texture)));//move so the original is in the map
	assert(inserted.second,
		"TextureManager::load : Failed to load (" + id + ") @ " + path + ". Possible id collision.");
}

////////////////////////////////////////////////////////////
///	\brief Used to retrieve texture from repo using it's
/// unique id
///
/// \param id Unique id used to refer to texture
///
////////////////////////////////////////////////////////////
sf::Texture& goo::TextureManager::get(std::string id)
{
	auto texture = m_textureMap.find(id);
	return *texture->second;
}

////////////////////////////////////////////////////////////
///	\brief Used to retrieve texture from repo using it's
/// unique id. This overload is used for refs and ptrs to
/// const TextureManagers
///
/// \param id Unique id used to refer to texture
///
////////////////////////////////////////////////////////////
const sf::Texture& goo::TextureManager::get(std::string id) const
{
	auto texture = m_textureMap.find(id);
	return *texture->second;
}

////////////////////////////////////////////////////////////
///	\brief Loads all the textures listed in the JSON file
/// "AssetPaths.json"
///
///	\param debug (optional) Prints how many textures are in
/// the map before and after load to console
///
////////////////////////////////////////////////////////////
void goo::TextureManager::loadTextures(bool debug)
{
	if (debug)
	{
		std::cout << "Textures before load : " << m_textureMap.size() << std::endl;
	}
	//Store json file in JSONValue m_root
	readJSONFile("AssetPaths.json");
	//check how many elements are under the 'Textures' heading
	int elements = m_root["Assets"]["Textures"].size();
	//Allocate space on the heap for 2 string arrays of size 'elements'
	m_names = new std::string[elements];
	m_paths = new std::string[elements];
	//Loop through elements to store their values
	for (int i = 0; i < elements; i++)
	{
		m_names[i] = m_root["Assets"]["Textures"][i]["Name"].asString().c_str();
		m_paths[i] = m_root["Assets"]["Textures"][i]["Path"].asString().c_str();
		load(m_names[i], m_paths[i]);
	}
	if (debug)
	{
		std::cout << "Textures before load : " << m_textureMap.size() << std::endl;
	}
}