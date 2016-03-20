////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 20/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "TextureManager.h"
#include <assert.h>

////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////
goo::TextureManager::TextureManager()
{

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