////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 20/03/16
///	Last Edit: 21/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "GameDataManager.h"
#include <assert.h>
#include <iostream>

////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////
goo::GameDataManager::GameDataManager()
{
	loadGameData(true);
}

////////////////////////////////////////////////////////////
///	\brief Loads a string from file @param value into the
/// games central font repo
///
/// \param id Unique id used to refer to font
///
/// \param value The string literal
///
////////////////////////////////////////////////////////////
void goo::GameDataManager::loadString(std::string id, const std::string value)
{
	//Create a pointer to a font created on the heap
	std::unique_ptr<std::string> stringPtr(new std::string(value));

	//insert() returns a pair<int,bool>. The int is it's iteration in the map
	//The bool is whether there was an id collision/successful insertion so we
	//store it and then assert it (insert a breakpoint if !boolean) and print
	//an error message if false
	auto inserted = m_stringMap.insert(std::make_pair(id, std::move(stringPtr)));//move so the original is in the map
	assert(inserted.second,
		"GameDataManager::load : Failed to load (" + id + "). Possible id collision.");
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
void goo::GameDataManager::loadValue(std::string id, const float value)
{
	//Create a pointer to a font created on the heap
	std::unique_ptr<float> numberPtr(new float(value));

	//insert() returns a pair<int,bool>. The int is it's iteration in the map
	//The bool is whether there was an id collision/successful insertion so we
	//store it and then assert it (insert a breakpoint if !boolean) and print
	//an error message if false
	auto inserted = m_valueMap.insert(std::make_pair(id, std::move(numberPtr)));//move so the original is in the map
	assert(inserted.second,
		"GameDataManager::load : Failed to load (" + id + "). Possible id collision.");
}

////////////////////////////////////////////////////////////
///	\brief Used to retrieve strings from repo using it's
/// unique id
///
/// \param id Unique id used to refer to string
///
////////////////////////////////////////////////////////////
std::string& goo::GameDataManager::getString(std::string id)
{
	auto string = m_stringMap.find(id);
	return *string->second;
}

////////////////////////////////////////////////////////////
///	\brief Used to retrieve strings from repo using it's
/// unique id. This overload is used for refs and ptrs to
/// const GameDataManagers
///
/// \param id Unique id used to refer to font
///
////////////////////////////////////////////////////////////
const std::string& goo::GameDataManager::getString(std::string id) const
{
	auto string = m_stringMap.find(id);
	return *string->second;
}

////////////////////////////////////////////////////////////
///	\brief Used to retrieve numbers from repo using it's
/// unique id
///
/// \param id Unique id used to refer to number
///
////////////////////////////////////////////////////////////
float& goo::GameDataManager::getValue(std::string id)
{
	auto number = m_valueMap.find(id);
	return *number->second;
}

////////////////////////////////////////////////////////////
///	\brief Used to retrieve numbers from repo using it's
/// unique id. This overload is used for refs and ptrs to
/// const GameDataManagers
///
/// \param id Unique id used to refer to number
///
////////////////////////////////////////////////////////////
const float& goo::GameDataManager::getValue(std::string id) const
{
	auto number = m_valueMap.find(id);
	return *number->second;
}

////////////////////////////////////////////////////////////
///	\brief Loads all the fonts listed in the JSON file
/// "AssetPaths.json"
///
///	\param debug (optional) Prints how many fonts are in the
/// map before and after load to console
///
////////////////////////////////////////////////////////////
void goo::GameDataManager::loadGameData(bool debug)
{
	//Store json file in JSONValue m_root
	readJSONFile("GameData.json");

	//Load strings
	if (debug)
	{
		std::cout << "Strings before load : " << m_stringMap.size() << std::endl;
	}
	//check how many elements are under the 'Strings' heading
	int elements = m_root["GameData"]["Strings"].size();
	//Allocate space on the heap for 2 string arrays of size 'elements'
	std::string *m_firstValue = new std::string[elements];
	std:: string *m_secondValue = new std::string[elements];
	//Loop through elements to store their values
	for (int i = 0; i < elements; i++)
	{
		m_firstValue[i] = m_root["GameData"]["Strings"][i]["ID"].asString().c_str();
		m_secondValue[i] = m_root["GameData"]["Strings"][i]["Value"].asString().c_str();
		loadString(m_firstValue[i], m_secondValue[i]);
	}
	if (debug)
	{
		std::cout << "Strings after load : " << m_stringMap.size() << std::endl;
	}

	//Load numbers
	if (debug)
	{
		std::cout << "Numbers before load : " << m_valueMap.size() << std::endl;
	}

	//check how many elements are under the 'Numbers' heading
	elements = m_root["GameData"]["Numbers"].size();
	//Allocate space on the heap for 2 string arrays of size 'elements'
	std::string *m_firstValue2 = new std::string[elements];
	float *m_numericalValue = new float[elements];
	//Loop through elements to store their values
	for (int i = 0; i < elements; i++)
	{
		m_firstValue2[i] = m_root["GameData"]["Numbers"][i]["ID"].asString().c_str();
		m_numericalValue[i] = m_root["GameData"]["Numbers"][i]["Value"].asFloat();
		loadValue(m_firstValue2[i], m_numericalValue[i]);
	}
	if (debug)
	{
		std::cout << "Numbers after load : " << m_valueMap.size() << std::endl;
	}

	delete[] m_firstValue;
	delete[] m_firstValue2;
	delete[] m_secondValue;
	delete[] m_numericalValue;
}