////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 22/03/16
///	Last Edit: 22/03/16
////////////////////////////////////////////////////////////
#ifndef GAMEDATAMANAGER_HEADER
#define GAMEDATAMANAGER_HEADER
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include "AssetLoader.h"

namespace goo
{
	////////////////////////////////////////////////////////////
	///	\brief A class that acts as a singular repository for
	/// game data
	///
	////////////////////////////////////////////////////////////
	class GameDataManager : AssetLoader
	{
	private:
		//string map
		std::map<std::string,	//key
			std::unique_ptr<std::string>> m_stringMap;	//value
		//float map
		std::map<std::string,	//key
			std::unique_ptr<float>> m_valueMap;	//value
		void loadGameData(bool debug = false);

	public:
		GameDataManager();
		void loadString(std::string id, const std::string value);
		void loadValue(std::string id, const float value);
		std::string& getString(std::string id);
		const std::string& getString(std::string id) const;
		float& getValue(std::string id);
		const float& getValue(std::string id) const;
	};
}
////////////////////////////////////////////////////////////
///	\class A class that acts as a singular repository for
/// game data. It loads a JSON and creates a map fom the
/// list of unique ids and strings of paths that are listed
/// in the file
///
////////////////////////////////////////////////////////////
#endif
