////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 19/03/16
///	Last Edit: 22/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include "ControllerDebugScreen.h"

////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////
goo::ControllerDebugScreen::ControllerDebugScreen(sf::RenderWindow& window, goo::AssetManager& assets, int& currentScreen) :
goo::Screen(window, assets, currentScreen)
{
	initialise();
}

////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////
goo::ControllerDebugScreen::~ControllerDebugScreen()
{
	delete[] m_buttonTexts;
}

////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
///	\brief Initial class setup
///
////////////////////////////////////////////////////////////
void goo::ControllerDebugScreen::initialise()
{
	////Load font for outputting m_displayedController's input values
	//if (!m_font.loadFromFile("../Assets/Fonts/KenPixel.ttf"))
	//{
	//	std::cout << "ControllerDebugScreen.cpp : Failed to load file 'KenPixel.ttf'" << std::endl;
	//}

	m_fontPtr = &m_assets.getFont("KenPixel");

	//Calculate how many texts are needed
	int buttonCount = sf::Joystick::getButtonCount(m_displayedController);

	//Create sf::Text for each button
	m_buttonTexts = new sf::Text[buttonCount + sf::Joystick::AxisCount];
	for (int i = 0; i < buttonCount; i++)
	{
		m_buttonTexts[i] = sf::Text();
		m_buttonTexts[i].setFont(*m_fontPtr);
		m_buttonTexts[i].setColor(sf::Color::Red);
		m_buttonTexts[i].setScale(sf::Vector2f(0.75, 0.75));
		//Create the string using a stream string to
		//concantenate ints and strings
		std::stringstream buttonString;
		buttonString << "Button " << i << " : ";
		m_buttonTexts[i].setString(buttonString.str());
		//Set origin to centre
		m_buttonTexts[i].setOrigin(m_buttonTexts[i].getLocalBounds().width / 2, m_buttonTexts[i].getLocalBounds().height / 2);
		//Set text's position to be evenly spaced down the center of the screen
		int x = 100;
		int y = (m_buttonTexts[i].getLocalBounds().height * 1.1) * (i + 1);
		m_buttonTexts[i].setPosition(sf::Vector2f(x, y));
	}
	for (int i = 0; i < sf::Joystick::AxisCount; i++)
	{
		m_buttonTexts[buttonCount + i] = sf::Text();
		m_buttonTexts[buttonCount + i].setFont(*m_fontPtr);
		m_buttonTexts[buttonCount + i].setColor(sf::Color::Red);
		m_buttonTexts[i].setScale(sf::Vector2f(0.75, 0.75));
		//Create the string using a stream string to
		//concantenate ints and strings
		std::stringstream buttonString;
		buttonString << "Axis " << i << " : ";
		m_buttonTexts[buttonCount + i].setString(buttonString.str());
		//Set origin to centre
		m_buttonTexts[buttonCount + i].setOrigin(m_buttonTexts[buttonCount + i].getLocalBounds().width / 2,
			m_buttonTexts[buttonCount + i].getLocalBounds().height / 2);
		//Set text's position to be evenly spaced down the center of the screen
		int x = m_window.getSize().x / 2;
		int y = (m_buttonTexts[buttonCount + i].getLocalBounds().height * 1.1) * (i + 1);
		m_buttonTexts[buttonCount + i].setPosition(sf::Vector2f(x, y));
	}
}

////////////////////////////////////////////////////////////
///	\brief Function that takes care of user input
///
/// \param e sf::Event to respond to
///
/// \param currentScreen Pointer to integer controlling
/// the current screen
///
////////////////////////////////////////////////////////////
void goo::ControllerDebugScreen::input(sf::Event e)
{
	checkForScreenClose(e);
}

////////////////////////////////////////////////////////////
///	\brief Called once a frame
///
/// \param elapsedTime Time passed since last frame
///
////////////////////////////////////////////////////////////
void goo::ControllerDebugScreen::update(sf::Time elapsedTime)
{
	int buttonCount = sf::Joystick::getButtonCount(m_displayedController);
	for (int i = 0; i < buttonCount; i++)
	{
		//Create the string using a stream string to
		//concantenate ints and strings
		std::stringstream buttonString;
		buttonString << "Button " << i << " : " << sf::Joystick::isButtonPressed(m_displayedController, i);
		m_buttonTexts[i].setString(buttonString.str());
	}
	for (int i = 0; i < sf::Joystick::AxisCount; i++)
	{
		//Create the string using a stream string to
		//concantenate ints and strings
		std::stringstream axisString;
		axisString << "Axis : " << i << " : " << sf::Joystick::getAxisPosition(m_displayedController, static_cast<sf::Joystick::Axis>(i));
		m_buttonTexts[buttonCount + i].setString(axisString.str());
	}
}

////////////////////////////////////////////////////////////
///	\brief Draws assets to the sf::Renderwindow
///
////////////////////////////////////////////////////////////
void goo::ControllerDebugScreen::draw()
{
	int buttonCount = sf::Joystick::getButtonCount(m_displayedController);
	for (int i = 0; i < buttonCount; i++)
	{
		m_window.draw(m_buttonTexts[i]);
	}
	for (int i = 0; i < sf::Joystick::AxisCount; i++)
	{
		m_window.draw(m_buttonTexts[buttonCount + i]);
	}
}

////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
///	\brief Change which controller input is displayed
/// on the screen
///
/// \param displayedController ControllerID enum to
/// select controller
///
////////////////////////////////////////////////////////////
void goo::ControllerDebugScreen::changeDisplayedConroller(goo::ControllerID displayedController)
{
	int controllerID = static_cast<int>(displayedController);
	if (controllerID >= 0 && controllerID < sf::Joystick::Count)
	{
		m_displayedController = controllerID;
	}
}
