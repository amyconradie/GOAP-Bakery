#include "Game.h"

Game::Game()
{
	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->m_RenderWindow;
}

void Game::initVariables()
{
	this->m_RenderWindow = nullptr;
}

void Game::initWindow()
{
	// create basic video mode
	this->m_VideoMode = sf::VideoMode(
		sf::VideoMode::getDesktopMode().width,
		sf::VideoMode::getDesktopMode().height
	);

	// create full screen window
	this->m_RenderWindow = new sf::RenderWindow(
		this->m_VideoMode,
		m_cTitle,
		sf::Style::Fullscreen | sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close
	);

	// set max frame rate
	this->m_RenderWindow->setFramerateLimit(60);

	// disable registering keys multiple times while they are pressed down
	this->m_RenderWindow->setKeyRepeatEnabled(false);

	// make sure top left corner is at position (0,0)
	this->m_RenderWindow->setPosition(sf::Vector2i(0, 0));

	// create and set view
	this->m_RenderWindow->setView(
		calcView(
			m_RenderWindow->getSize(),
			sf::Vector2f(
				sf::VideoMode::getDesktopMode().width,
				sf::VideoMode::getDesktopMode().height)
		)
	);

	// store current window size for future use in the MaintainAspectRatio() function
	this->m_v2uOldWindowSize = this->m_RenderWindow->getSize();
}

// rescales window to match viewport size
// calls calcView to determine the appropriate aspectRatio based on the user's monitor
void Game::MaintainAspectRatio(bool _bRescaleWindow)
{
	// creates black letterboxing
	// makes sure aspect ratio is not distorted by adding black letterboxing
	// create new view
	this->m_RenderWindow->setView(
		calcView(
			m_RenderWindow->getSize(), 
			sf::Vector2f(
				sf::VideoMode::getDesktopMode().width,
				sf::VideoMode::getDesktopMode().height
			)
		)
	);

	if (_bRescaleWindow)
	{
		float wProportions = 0;
		float hProportions = 0;
		float newWidth = this->m_RenderWindow->getSize().x;
		float newHeight = this->m_RenderWindow->getSize().y;
		float newPosLeft = this->m_RenderWindow->getPosition().x;
		float newPosTop = this->m_RenderWindow->getPosition().y;

		// height is larger than it should be
		// window width was decreased
		// make height smaller to match
		if (this->m_v2uOldWindowSize.x > this->m_RenderWindow->getSize().x)
		{
			hProportions = this->m_RenderWindow->getView().getViewport().top * 2;
			newHeight = this->m_RenderWindow->getSize().y - (this->m_RenderWindow->getSize().y * hProportions);
		}

		// width is larger than it should be
		// window height was decreased
		// make width smaller to match
		if (this->m_v2uOldWindowSize.y > this->m_RenderWindow->getSize().y)
		{
			wProportions = this->m_RenderWindow->getView().getViewport().left * 2;
			newWidth = this->m_RenderWindow->getSize().x - (this->m_RenderWindow->getSize().x * wProportions);
		}

		/*
			!!! ALERT !!!
			- this part only kind of works
			- increasing window size seems to keep letterboxing when it shouldn't
			- unsure what conditions to set when scaling window up
		*/

		double widthRatio = (double)this->m_v2uOldWindowSize.x / sf::VideoMode::getDesktopMode().width;
		double heightRatio = (double)this->m_v2uOldWindowSize.y / sf::VideoMode::getDesktopMode().height;

		// width is smaller than it should be
		// window height was increased
		// make width larger to match
		if (this->m_v2uOldWindowSize.y < this->m_RenderWindow->getSize().y)
		{
			wProportions = this->m_RenderWindow->getView().getViewport().width;
			 newWidth = this->m_RenderWindow->getSize().x * wProportions;
		}

		// height is smaller than it should be
		// window width was increased
		// make height larger to match
		if ( this->m_v2uOldWindowSize.x < this->m_RenderWindow->getSize().x)
		{
			hProportions = this->m_RenderWindow->getView().getViewport().height;
			newHeight = this->m_RenderWindow->getSize().y * hProportions;
		}
		
		// implement changes to window
		this->m_RenderWindow->setSize(
			sf::Vector2u(
				round(newWidth), 
				round(newHeight)
			)
		);
		this->m_v2uOldWindowSize = this->m_RenderWindow->getSize();
	}
}

// on "alt + enter" switch between windowedand fullscreen modes
void Game::toggleFullscreen()
{
	if (this->m_bToggle)
	{
		// create windowed screen
		this->m_VideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
		this->m_RenderWindow->create(
			this->m_VideoMode, 
			m_cTitle, 
			sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close
		);

		// set window size to 75% of fullscreen
		this->m_RenderWindow->setSize(  
			sf::Vector2u(
				this->m_VideoMode.width * 0.75, 
				this->m_VideoMode.height * 0.75
			)
		);

		// set window position to the center of the monitor
		this->m_RenderWindow->setPosition(
			sf::Vector2i(
				(sf::VideoMode::getDesktopMode().width - this->m_RenderWindow->getSize().x) * 0.4, 
				(sf::VideoMode::getDesktopMode().height - this->m_RenderWindow->getSize().y) * 0.4
			)
		);
	}
	else
	{
		// create fullscreen
		this->m_RenderWindow->create(this->m_VideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), m_cTitle, sf::Style::Fullscreen);
	}

	// forces view to maintain the correct aspect ratio
	// and brute forces window size to match the view size
	MaintainAspectRatio(true); 

	// switch toggle to opposite setting
	this->m_bToggle = !this->m_bToggle; 
}

//	creates a new view with the correct size based on a given aspect ratio
sf::View Game::calcView(sf::Vector2u _v2uWindowSize, sf::Vector2f _v2fDesignedSize)
{
	sf::FloatRect viewport(0.f, 0.f, 1.f, 1.f);

	float screenwidth = _v2uWindowSize.x / static_cast<float>(_v2fDesignedSize.x);
	float screenheight = _v2uWindowSize.y / static_cast<float>(_v2fDesignedSize.y);

	if (screenwidth > screenheight)
	{
		viewport.width = screenheight / screenwidth;
		viewport.left = (1.f - viewport.width) / 2.f;
	}
	else if (screenwidth < screenheight)
	{
		viewport.height = screenwidth / screenheight;
		viewport.top = (1.f - viewport.height) / 2.f;
	}

	sf::View view(sf::FloatRect(0, 0, _v2fDesignedSize.x, _v2fDesignedSize.y));
	view.setViewport(viewport);

	return view;
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

sf::Event Game::pollEvents(Scene* _scene, sf::Event* _event)
{
	while (this->m_RenderWindow->pollEvent(*_event))
	{
		switch (_event->type )
		{

		// If "close"/"x" button is pressed, close the game/app
		case sf::Event::Closed:
			this->m_RenderWindow->close();
			break;

		case sf::Event::KeyPressed:

			// If "Esc" key is pressed, close the game/app
			if (_event->key.code == sf::Keyboard::Escape)
			{
				this->m_RenderWindow->close();
			}

			// Toggle Full Screen by pressing the "Alt + Enter" keys
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)) && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				this->toggleFullscreen();
			}
			break;

		// If Screen is Resized maintain the aspect ratio
		case sf::Event::Resized:
			MaintainAspectRatio(true);
			break;

		}
	}

	// get elapsed time and restart timer
	sf::Time timer = m_Clock.restart(); 

	// get the delta time
	float dtime = timer.asSeconds(); 

	// update and poll events inside the scene
	_scene->update(dtime, _event);

	return *_event;
}

// updates game by by updating the scene that is open
void Game::update(Scene* _scene, sf::Event* _event)
{
	pollEvents(_scene, _event);
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



const char* Game::getTitle() 
{ 
	return this->m_cTitle; 
};



void Game::setTitle(const char* _cTitle) 
{ 
	this->m_cTitle = _cTitle; 
};