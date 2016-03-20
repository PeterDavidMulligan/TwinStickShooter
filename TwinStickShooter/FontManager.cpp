////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 20/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "FontManager.h"
#include <assert.h>

////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////
goo::FontManager::FontManager()
{

}

////////////////////////////////////////////////////////////
///	\brief Loads a font from file @param path into the
/// games central font repo
///
/// \param id Unique id used to refer to font
///
/// \param path Relative path to font
///
////////////////////////////////////////////////////////////
void goo::FontManager::load(std::string id, const std::string path)
{
	//Create a pointer to a font created on the heap
	std::unique_ptr<sf::Font> font(new sf::Font());
	//load the font
	font->loadFromFile(path);
	//insert() returns a pair<int,bool>. The int is it's iteration in the map
	//The bool is whether there was an id collision/successful insertion so we
	//store it and then assert it (insert a breakpoint if !boolean) and print
	//an error message if false
	auto inserted = m_fontMap.insert(std::make_pair(id, std::move(font)));//move so the original is in the map
	assert(inserted.second,
		"FontManager::load : Failed to load (" + id + ") @ " + path + ". Possible id collision.");
}

////////////////////////////////////////////////////////////
///	\brief Used to retrieve font from repo using it's
/// unique id
///
/// \param id Unique id used to refer to font
///
////////////////////////////////////////////////////////////
sf::Font& goo::FontManager::get(std::string id)
{
	auto font = m_fontMap.find(id);
	return *font->second;
}

////////////////////////////////////////////////////////////
///	\brief Used to retrieve font from repo using it's
/// unique id. This overload is used for refs and ptrs to
/// const FontManagers
///
/// \param id Unique id used to refer to font
///
////////////////////////////////////////////////////////////
const sf::Font& goo::FontManager::get(std::string id) const
{
	auto font = m_fontMap.find(id);
	return *font->second;
}