/*

	For now, all actions are updated all the time
	
	TODO
	-change all player/bullets translations into TIME based updates
	-change collision checks to be called only ONCE PER FRAME
	-organize code - I'd like to have one naming convention,
	 probably will pick google c++ style guide
	-check other files for potential TODOs
	-in Player class change player ID to size_t, negative values are unwanted

*/

#include"AllHeaders.h"

int main()
{
	srand(time(NULL));

	Game MyGame;

	// Create the main window
	sf::RenderWindow app(sf::VideoMode(MyGame.AccessConfigs().getRes().WIDTH, MyGame.AccessConfigs().getRes().HEIGHT), "Just some boxes", sf::Style::Fullscreen);
	app.setFramerateLimit(60);

	// Start the game loop
	while (app.isOpen())
	{
		// Clear screen
		app.clear();

		// All updates are included in Game class.
		// Therfore updating MyGame updates: Scene, Player, GUI
		MyGame.Update(app);

		// Display window
		app.display();

		// Process events
		sf::Event event;
		while (app.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				app.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			{
				app.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				MyGame.InDebug = true;
			}
			if (sf::Joystick::isButtonPressed(0, 1))
			{
				app.close();
			}
		}
	}

	return EXIT_SUCCESS;
}