////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 21/03/16
///	Last Edit: 22/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include "AssetLoader.h"

////////////////////////////////////////////////////////////
///	\brief Reads a JSON file into m_root
///
/// \param path Relative path to the JSON file
///
/// \param debug (optional) Prints json file to console
///
////////////////////////////////////////////////////////////
void goo::AssetLoader::readJSONFile(std::string path, bool debug)
{
	//Read in the file using a filestream
	std::ifstream jsonFile(path, std::ifstream::binary);
	//Simultaneously parse and check parse success
	bool parsingSuccessful = m_reader.parse(jsonFile, m_root, false);
	//Print the built in error message if parse fails
	if (!parsingSuccessful)
	{
		// report to the user the failure and their locations in the document.
		std::cout << "Failed to parse configuration\n"
			<< m_reader.getFormattedErrorMessages();
	}
	//output file to console
	if (debug)
	{
		std::cout << m_root << std::endl;
	}
}