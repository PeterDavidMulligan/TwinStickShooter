////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 22/03/16
///	Last Edit: 22/03/16
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "AssetManager.h"
////////////////////////////////////////////////////////////
///	\brief Returns a reference to the Texture
///
/// \param id Unique identifier of Texture 
///
/// \return A reference to the Texture id
///
////////////////////////////////////////////////////////////
sf::Texture& goo::AssetManager::getTexture(std::string id)
{
	return m_textures.get(id);
}
////////////////////////////////////////////////////////////
///	\brief Returns a reference to the SoundBuffer
///
/// \param id Unique identifier of SoundBuffer id
///
/// \return A reference to the SoundBuffer id
///
////////////////////////////////////////////////////////////
sf::SoundBuffer& goo::AssetManager::getSoundBuffer(std::string id)
{
	return m_sounds.get(id);
}
////////////////////////////////////////////////////////////
///	\brief Returns a reference to the Font
///
/// \param id Unique identifier of Font id
///
/// \return A reference to the Font id
///
////////////////////////////////////////////////////////////
sf::Font& goo::AssetManager::getFont(std::string id)
{
	return m_fonts.get(id);
}