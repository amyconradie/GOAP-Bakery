#ifndef BASICSCENE_H
#define BASICSCENE_H

#include "pch.h"
#include "Scene.h"

class BasicScene : public Scene
{
private:
	sf::RenderWindow* window;
	const char* sceneTitle = "BasicScene";

public:
	BasicScene();
	virtual ~BasicScene();
	virtual void init(sf::RenderWindow* _window);
	virtual void update(float dtime, sf::Event* event);
	virtual void render();
	virtual const char* getTitle();
};

#endif