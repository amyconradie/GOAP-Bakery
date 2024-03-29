
#ifndef GAME_H
#define GAME_H

#include "pch.h"
#include "Scene.h"

/*
	this is an instance of the Game/App
	-
*/
class Game
{

private:

	// private variables
	//-------------------

	sf::RenderWindow* m_RenderWindow;
	sf::VideoMode* m_VideoMode;
	sf::Clock m_Clock;
	const char* m_cTitle;


	// private functions
	//-------------------

	void initVariables();
	void initWindow();

public:

	// constructors & destructors
	//----------------------------

	Game();
	~Game();


	// accessors
	//-----------

	const bool running();


	// important functions
	//---------------------

	void update(Scene* _scene, sf::Event* _event);
	void render(Scene* _scene);
	void run(Scene* _scene, sf::Event* _event);


	// other functions
	//-----------------

	void setWindowTitle(const char* _cTitle);
	void closeWindow();
	sf::RenderWindow* getWindow();
	sf::VideoMode* getVideoMode();
	const char* getTitle();
	void setTitle(const char* _cTitle);
};

#endif