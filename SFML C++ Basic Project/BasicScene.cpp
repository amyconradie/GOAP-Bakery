#include "BasicScene.h"

BasicScene::BasicScene()
{
	this->m_RenderWindow = nullptr;
}

BasicScene::~BasicScene()
{
	for (auto& gameObject : m_vgGameObjects) 
	{
		delete gameObject;
	}
}

void BasicScene::init(sf::RenderWindow* _window)
{
	this->m_RenderWindow = _window;
	updateMousePositions(1);

	// add BG first, so it renders first
	GameObject* gBG = new GameObject;
	//gBG->init(this->m_RenderWindow, "sourfrog.png", sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), true); //image tiling
	//gBG->init(this->m_RenderWindow, "sourfrog.png", sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), false); //image stretched to fit a desired size
	gBG->init(this->m_RenderWindow, this->m_RenderWindow->getSize().x, this->m_RenderWindow->getSize().y, sf::Color::Blue); // fill color bg
	m_vgGameObjects.push_back(gBG);

	// other objects
	GameObject* go = new GameObject;
	go->init(this->m_RenderWindow, "sourfrog.png", 100, 100, false);
	go->setOriginToCenter();
	go->setPosition(sf::Vector2f(this->m_RenderWindow->getSize().x / 2, this->m_RenderWindow->getSize().y / 2));
	m_vgGameObjects.push_back(go);
}

void BasicScene::update(float _fDeltaTime, sf::Event* event)
{
	switch (event->type) 
	{
		case sf::Event::MouseButtonReleased: // detect mouse clicks
			if (sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left)
			{
				updateMousePositions(_fDeltaTime);
			}
			break;

		default:
			break;
	}
}

sf::WindowHandle BasicScene::GetWindowHandle() {
	return m_RenderWindow->getSystemHandle();
}

void BasicScene::render()
{
	// render gameObjects & widgets
	// whatever is drawn last, will be the top layer

	// BackGround First
	this->m_vgGameObjects[0]->render();

	// sf::RenderTexture/painting canvas/view/whatever it's called

	// gameObjects

	/*
		renders BackGround first, then other objects in the order they were added
	*/
	for (auto& gameObject : m_vgGameObjects)
	{
		gameObject->render();
	}

	// widgets

	// ui elements in widgets

	// other ui elements
}

const char* BasicScene::getTitle() 
{ 
	return this->m_cTitle;
}

void BasicScene::setTitle(const char* _sceneTitle)
{
	this->m_cTitle = _sceneTitle;
}

bool areSame(double x, double y) 
{
	return std::fabs(x - y) <= std::numeric_limits<double>::epsilon();
}

// stores when mousePosition Changes
void BasicScene::updateMousePositions(float _fDeltaTime)
{
	sf::Vector2i v2iTempMPW = sf::Mouse::getPosition(*this->m_RenderWindow);
	sf::Vector2f v2fTempMPV = this->m_RenderWindow->mapPixelToCoords(this->m_v2iMousePosWindow);

	float _fTimeBtwnClicks = 0.01;

	if (!areSame(this->m_v2iMousePosWindow.x, v2iTempMPW.x) || _fDeltaTime > _fTimeBtwnClicks)
	{
		this->m_v2iMousePosWindow.x = v2iTempMPW.x;
		std::cout << "MousePosWindow X: " << m_v2iMousePosWindow.x << std::endl;
	}

	if (!areSame(this->m_v2iMousePosWindow.y, v2iTempMPW.y) || _fDeltaTime > _fTimeBtwnClicks)
	{
		this->m_v2iMousePosWindow.y = v2iTempMPW.y;
		std::cout << "MousePosWindow Y: " << m_v2iMousePosWindow.y << std::endl;
	}

	if (!areSame(this->m_v2fMousePosView.x, v2fTempMPV.x) || _fDeltaTime > _fTimeBtwnClicks)
	{
		this->m_v2fMousePosView.x = v2fTempMPV.x;
		std::cout << "MousePosView X:" << m_v2fMousePosView.x << std::endl;
	}

	if (!areSame(this->m_v2fMousePosView.y, v2fTempMPV.y) || _fDeltaTime > _fTimeBtwnClicks)
	{
		this->m_v2fMousePosView.y = v2fTempMPV.y;
		std::cout << "MousePosView Y:" << m_v2fMousePosView.x << std::endl;
	}

}
