#include "BasicScene.h"

BasicScene::BasicScene()
{
	this->window = nullptr;
}

BasicScene::~BasicScene()
{

}

void BasicScene::init(sf::RenderWindow* _window)
{
	this->window = _window;
}

void BasicScene::update(float dtime, sf::Event* event)
{
	switch (event->type) 
	{
		case sf::Event::MouseButtonReleased:
			if (sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f clickPos = sf::Vector2f((float)(sf::Mouse::getPosition(*this->window).x), (float)(sf::Mouse::getPosition(*this->window).y));
				std::cout << "Mouse Clicked at: x:" << clickPos.x << ", y: " << clickPos.y << std::endl;
			}
			break;

		default:
			break;
	}
}

void BasicScene::render()
{
	// render game items
}

const char* BasicScene::getTitle() 
{ 
	return this->sceneTitle;
}