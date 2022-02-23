#include "pch.h"
#include "Game.h"
#include "BasicScene.h"

int main() {

	// Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	bool quit = false;
	sf::Event event;

	Game* game = new Game;
	Scene* current_scene = new BasicScene;

	current_scene->init(game->getWindow());
	game->setWindowTitle(current_scene->getTitle());

	// Game Loop
	while (game->running() || !quit)
	{
		// Update & Render Game Scene
		game->run(current_scene, &event); // polls event inside game scene

		// Update Game
		game->getWindow()->pollEvent(event); // polls event inside game

		switch (event.type)
		{
			case sf::Event::KeyPressed:

				if (event.key.code == sf::Keyboard::Num1) // this if statement creates a new scene
				{
					delete(current_scene);
					current_scene = new BasicScene;
					current_scene->init(game->getWindow());
					game->setWindowTitle(current_scene->getTitle());
					std::cout << "New Scene Created: " << current_scene->getTitle() << std::endl;
				}

				if (event.key.code == sf::Keyboard::Escape)
				{
					quit = true;
					delete(current_scene);
					game->closeWindow();
					std::cout << "Quitting Game" << std::endl;
				}

				// insert more shortcuts here by adding more if statements ^^^

				break;

			case sf::Event::Closed: // window 'x' button
				quit = true;
				delete(current_scene);
				game->closeWindow();
				std::cout << "Quitting Game" << std::endl;
				break;
		}
	}

	return 0;
}