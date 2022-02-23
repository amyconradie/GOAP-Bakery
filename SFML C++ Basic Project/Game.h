
#ifndef GAME_H
#define GAME_H

#include "pch.h"
#include "Scene.h"

class Game
{
private:

	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;

	// Mouse Positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	sf::Clock clock;
	const char* gameName = "Game Name";

	void initVariables();
	void initWindow();


public:

	// constructors & destructors
	Game();
	~Game();

	// accessors

	const bool running();

	// functions

	void setWindowTitle(const char* title);
	sf::Event pollEvents(Scene* behaviour, sf::Event* event);
	void update(Scene* behaviour, sf::Event* event);
	void render(Scene* behaviour);
	void run(Scene* behaviour, sf::Event* event);
	void closeWindow();
	sf::RenderWindow* getWindow();
	void updateMousePositions();
};

#endif