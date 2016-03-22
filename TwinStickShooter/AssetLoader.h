////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 21/03/16
///	Last Edit: 22/03/16
////////////////////////////////////////////////////////////
#ifndef ASSETLOADER_HEADER
#define ASSETLOADER_HEADER
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <memory>
#include "json\json.h"

namespace goo
{
	////////////////////////////////////////////////////////////
	///	\brief A baseclass for other asset managers
	////////////////////////////////////////////////////////////
	class AssetLoader
	{
		////////////////////////////////////////////////////////////
		// Member Variables
		////////////////////////////////////////////////////////////
	protected:
		Json::Value m_root;	//Stores the JSON file
		Json::Reader m_reader;	//Used by sublclasses to parse m_root
		std::string *m_paths;	//Array of paths to assets loaded by subclasses
		std::string *m_names;	//Array unique ids for assets loaded by subclasses
		void readJSONFile(std::string path, bool debug = false);	//reads json into m_root
	};
}
////////////////////////////////////////////////////////////
///	\class A baseclass for other asset managers. Includes
/// function loadJSONFile to store a JSON file in the
/// Json::Value m_root
///
////////////////////////////////////////////////////////////
#endif