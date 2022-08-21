#include "Game.h"

Game::Game()
{
	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->m_RenderWindow;
	delete this->m_VideoMode;
}

void Game::initVariables()
{
	this->m_RenderWindow = nullptr;
	this->m_VideoMode = nullptr;
}

void Game::initWindow()
{
	// create basic video mode
	this->m_VideoMode = new sf::VideoMode(
		sf::VideoMode::getDesktopMode().width,
		sf::VideoMode::getDesktopMode().height
	);

	// create full screen window
	this->m_RenderWindow = new sf::RenderWindow(
		*m_VideoMode,
		m_cTitle,
		sf::Style::Fullscreen | sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close
	);

	// set max frame rate
	this->m_RenderWindow->setFramerateLimit(60);

	// disable registering keys multiple times while they are pressed down
	this->m_RenderWindow->setKeyRepeatEnabled(false);

	// make sure top left corner is at position (0,0)
	this->m_RenderWindow->setPosition(sf::Vector2i(0, 0));

}

void Game::setWindowTitle(const char* _cTitle)
{
	this->m_RenderWindow->setTitle(_cTitle);
}

// checks that the renderWindow is still open
const bool Game::running()
{
	return this->m_RenderWindow->isOpen();
}

// updates game by by updating the scene that is open
void Game::update(Scene* _scene, sf::Event* _event)
{
	// get elapsed time and restart timer
	sf::Time timer = m_Clock.restart();

	// get the delta time
	float dtime = timer.asSeconds();

	// update and poll events inside the scene
	_scene->update(dtime, _event);
}

// draws everything in the game
// - clears window
// - draws objects in the scene
// - displays drawn objects in the window
void Game::render(Scene* _scene)
{
	// clear previous frame
	this->m_RenderWindow->clear();

	// draw game objects, widgets and ui elements
	_scene->render();

	// display frame
	this->m_RenderWindow->display();
}

void Game::run(Scene* _scene, sf::Event* _event)
{
	update(_scene, _event);
	render(_scene);
}

void Game::closeWindow()
{
	this->m_RenderWindow->close();
}

sf::RenderWindow* Game::getWindow()
{
	return this->m_RenderWindow;
}

sf::VideoMode* Game::getVideoMode()
{
	return this->m_VideoMode;
}

const char* Game::getTitle()
{
	return this->m_cTitle;
};

void Game::setTitle(const char* _cTitle)
{
	this->m_cTitle = _cTitle;
};