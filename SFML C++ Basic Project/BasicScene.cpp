#include "BasicScene.h"

BasicScene::BasicScene()
{
	this->m_RenderWindow = nullptr;
}

BasicScene::~BasicScene()
{
	// makes sure any pointers are deleted when the scene is destroyed
	for (auto& gameObject : m_vgGameObjects) 
		delete gameObject;
}

// pretty much the entire setup for the scene should go in here
void BasicScene::init(sf::RenderWindow* _window)
{
	this->m_RenderWindow = _window;
	updateMousePositions(1);

	GameObject* gBG = new GameObject;
	gBG->init(this->m_RenderWindow, this->m_RenderWindow->getSize().x, this->m_RenderWindow->getSize().y, sf::Color(76, 47, 99)); // fill color bg
	m_vgGameObjects.push_back(gBG); // add BG first, so it renders first i.e. its the bottom layer

	// other objects
	GameObject* go = new GameObject;
	go->init(this->m_RenderWindow, "sourfrog.png", 100, 100, false);
	go->setOriginToCenter();
	go->setPosition(sf::Vector2f(this->m_RenderWindow->getSize().x / 2, this->m_RenderWindow->getSize().y / 2));
	m_vgGameObjects.push_back(go);
}

// updates the scene
// - updates mouse click positions
void BasicScene::update(float _fDeltaTime, sf::Event* event)
{
	switch (event->type) 
	{
		case sf::Event::MouseButtonReleased: // detect mouse clicks when released
			if (sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left)
			{
				updateMousePositions(_fDeltaTime); // prevents repeat clicks too quickly
			}
			break;

		default:
			break;
	}
}

// draws all the drawable objects in the scene
void BasicScene::render()
{
	// renders objects in the order they were added
	for (auto& gameObject : m_vgGameObjects)
	{
		gameObject->render();
	}

	// render other sprites/shapes here
}

const char* BasicScene::getTitle() 
{ 
	return this->m_cTitle;
}

void BasicScene::setTitle(const char* _sceneTitle)
{
	this->m_cTitle = _sceneTitle;
}

// compares doubles to see if they are the exact same value
bool areSame(double x, double y) 
{
	return std::fabs(x - y) <= std::numeric_limits<double>::epsilon();
}

// stores when mousePosition Changes
// makes sure click isnt registered multiple times
// if it's too close in time to the previous click 
// or it's in the exact same place
void BasicScene::updateMousePositions(float _fDeltaTime)
{
	sf::Vector2i v2iTempMPW = sf::Mouse::getPosition(*this->m_RenderWindow);
	sf::Vector2f v2fTempMPV = this->m_RenderWindow->mapPixelToCoords(this->m_v2iMousePosWindow);

	float _fTimeBtwnClicks = 0.01;

	if (!areSame(this->m_v2iMousePosWindow.x, v2iTempMPW.x) || _fDeltaTime > _fTimeBtwnClicks)
		this->m_v2iMousePosWindow.x = v2iTempMPW.x;

	if (!areSame(this->m_v2iMousePosWindow.y, v2iTempMPW.y) || _fDeltaTime > _fTimeBtwnClicks)
		this->m_v2iMousePosWindow.y = v2iTempMPW.y;

	if (!areSame(this->m_v2fMousePosView.x, v2fTempMPV.x) || _fDeltaTime > _fTimeBtwnClicks)
		this->m_v2fMousePosView.x = v2fTempMPV.x;

	if (!areSame(this->m_v2fMousePosView.y, v2fTempMPV.y) || _fDeltaTime > _fTimeBtwnClicks)
		this->m_v2fMousePosView.y = v2fTempMPV.y;
}
