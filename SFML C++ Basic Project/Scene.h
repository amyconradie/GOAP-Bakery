#ifndef SCENE_H
#define SCENE_H

#include "pch.h"

class Scene
{

public:

	// constructors & destructors
	Scene() {};
	virtual ~Scene() {};

	// functions
	virtual void init(sf::RenderWindow* _window) {};
	virtual void update(float dtime, sf::Event* event) = 0;
	virtual void render() = 0;
	virtual const char* getTitle() { return ""; };

};

#endif