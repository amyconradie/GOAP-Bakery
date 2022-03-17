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


void Game::MaintainAspectRatio(bool _bRescaleWindow)
{
	// creates black letterboxing, and makes sure aspect ratio is not distorted by adding black letterboxing
	this->m_RenderWindow->setView(calcView(m_RenderWindow->getSize(), sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height))); // recreate the view

	if (_bRescaleWindow)
	{
		float wProportions = 0, hProportions = 0, newWidth = this->m_RenderWindow->getSize().x, newHeight = this->m_RenderWindow->getSize().y, newPosLeft = this->m_RenderWindow->getPosition().x, newPosTop = this->m_RenderWindow->getPosition().y;

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
			this part only kind of works
			increasing window size seems to keep letterboxing
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
		
		this->m_RenderWindow->setSize(sf::Vector2u(round(newWidth), round(newHeight)));
		this->m_v2uOldWindowSize = this->m_RenderWindow->getSize();
	}
}


void Game::toggleFullscreen()
{
	if (this->m_bToggle)
	{
		this->m_VideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

		this->m_RenderWindow->create(this->m_VideoMode, m_cTitle, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);

		float fTempSizePercent = 0.75;
		this->m_RenderWindow->setSize(sf::Vector2u(this->m_VideoMode.width * fTempSizePercent, this->m_VideoMode.height * fTempSizePercent));

		sf::Vector2i v2iTopLeftCornerPos = sf::Vector2i((sf::VideoMode::getDesktopMode().width - this->m_RenderWindow->getSize().x)*0.4, (sf::VideoMode::getDesktopMode().height - this->m_RenderWindow->getSize().y) * 0.4);
		this->m_RenderWindow->setPosition(v2iTopLeftCornerPos);
	}
	else
	{
		// create fullscreen
		this->m_RenderWindow->create(this->m_VideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), m_cTitle, sf::Style::Fullscreen);
	}

	MaintainAspectRatio(true);
	this->m_bToggle = !this->m_bToggle; // switch fullscreen toggle
}



void Game::initWindow()
{
	// create basic video mode
	this->m_VideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

	// create full screen window
	this->m_RenderWindow = new sf::RenderWindow(this->m_VideoMode, m_cTitle, sf::Style::Fullscreen | sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);

	// set max frame rate
	this->m_RenderWindow->setFramerateLimit(60);
	this->m_RenderWindow->setKeyRepeatEnabled(false);

	// make sure top left corner is at position (0,0)
	this->m_RenderWindow->setPosition(sf::Vector2i(0,0));

	// create and set view
	this->m_RenderWindow->setView(calcView(m_RenderWindow->getSize(), sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)));

	// store current window size
	this->m_v2uOldWindowSize = this->m_RenderWindow->getSize();
}



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

		// If "Esc" key is pressed, close the app
		case sf::Event::Closed:
			this->m_RenderWindow->close();
			break;

		case sf::Event::KeyPressed:

			// If "Esc" key is pressed, close the app
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

		// If Screen is Resized, maintain aspect ratio
		case sf::Event::Resized:
			//this->m_RenderWindow->setView(calcView(sf::Vector2u(_event->size.width, _event->size.height), sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)));
			MaintainAspectRatio(true);
			break;

		}
	}

	sf::Time timer = m_Clock.restart(); // get elapsed time and restart timer
	float dtime = timer.asSeconds(); // delta time
	_scene->update(dtime, _event);

	return *_event;
}



void Game::update(Scene* _scene, sf::Event* _event)
{
	pollEvents(_scene, _event);
}



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