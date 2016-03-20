////////////////////////////////////////////////////////////
///	Author: Peter Mulligan
///	Date: 14/03/16
///	Last Edit: 14/03/16
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include "SFML\Graphics.hpp"
#include "Screens.h"
#include "TwinStickShooter\TextureManager.h"
#include "TwinStickShooter\FontManager.h"
#include "TwinStickShooter\SoundManager.h"

////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////
int currentScreen = 0;

////////////////////////////////////////////////////////////
///	\brief main is the root function for the game
///
/// \return returns 0 like any main function
////////////////////////////////////////////////////////////
int main()
{
	//Window setup
	sf::RenderWindow window(sf::VideoMode(800, 600), "Twin Stick" /*, sf::Style::Fullscreen*/);
	window.setVerticalSyncEnabled(true);

	//Resource managers
	goo::TextureManager textureManager;
	goo::SoundManager soundManager;
	goo::FontManager fontManager;
	
	//Screens Setup
	std::vector<goo::Screen*> screenContainer;	//Contains all the screens
	goo::TestScreen testScreen(window, textureManager, soundManager, fontManager);
	screenContainer.push_back(&testScreen);
	goo::ControllerDebugScreen controllerDebugScreen(window, textureManager, soundManager, fontManager);
	screenContainer.push_back(&controllerDebugScreen);
	
	//Clock setup & FPS setup
	sf::Clock clock;	
	const float FPS = 1.0f / 60;
	sf::Time elapsedTime;

	//Loops
	while (window.isOpen())
	{
		//INPUT LOOP
		sf::Event e;
		while (window.pollEvent(e))
		{	//Send input to the current screen
			screenContainer.at(currentScreen)->input(e, &currentScreen);
		}

		//GAME LOOP
		elapsedTime += clock.restart();	//Add time since last update
		if (elapsedTime.asSeconds() > FPS)	//If it's been long enough...
		{			
			//Update current screen
			screenContainer.at(currentScreen)->update(elapsedTime);
			//Draw the current screen
			window.clear(sf::Color::Black);
			screenContainer.at(currentScreen)->draw();		
			//Display current frame
			window.display();
			//Reset timer
			elapsedTime = elapsedTime.Zero;
		}
	}
	return 0;
}