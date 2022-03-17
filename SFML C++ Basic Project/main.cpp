#include "pch.h"
#include "Game.h"
#include "BasicScene.h"

int main() {

	std::srand(static_cast<unsigned>(time(NULL))); // init srand

	sf::Event event;
	Game* game = new Game();
	Scene* current_scene = new BasicScene(); // base class pointer

	game->setTitle("NEW GAME");
	game->setWindowTitle(game->getTitle());
	current_scene->init(game->getWindow());

	/*
		what about state switching from pause to play?
	*/

	// Game Loop
	while (game->running())
	{
		// Update & Render Scene (polls event inside active scene)
		game->run(current_scene, &event);
	}

	return 0;
}