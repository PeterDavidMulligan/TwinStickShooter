////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 21/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "FontManager.h"
#include <assert.h>
#include <iostream>

////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////
goo::FontManager::FontManager()
{
	loadFonts();
}
////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////
goo::FontManager::~FontManager()
{
	delete[] m_names;
	delete[] m_paths;
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

////////////////////////////////////////////////////////////
///	\brief Loads all the fonts listed in the JSON file
/// "AssetPaths.json"
///
///	\param debug (optional) Prints how many fonts are in the
/// map before and after load to console
///
////////////////////////////////////////////////////////////
void goo::FontManager::loadFonts(bool debug)
{
	if (debug)
	{
		std::cout << "Fonts before load : " << m_fontMap.size() << std::endl;
	}	
	//Store json file in JSONValue m_root
	readJSONFile("AssetPaths.json");
	//check how many elements are under the 'Textures' heading
	int elements = m_root["Assets"]["Fonts"].size();
	//Allocate space on the heap for 2 string arrays of size 'elements'
	m_names = new std::string[elements];
	m_paths = new std::string[elements];
	//Loop through elements to store their values
	for (int i = 0; i < elements; i++)
	{
		m_names[i] = m_root["Assets"]["Fonts"][i]["Name"].asString().c_str();
		m_paths[i] = m_root["Assets"]["Fonts"][i]["Path"].asString().c_str();
		load(m_names[i], m_paths[i]);
	}
	if (debug)
	{
		std::cout << "Fonts after load : " << m_fontMap.size() << std::endl;
	}
}