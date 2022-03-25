#ifndef SCENE_H
#define SCENE_H

#include "pch.h"
#include "GameObject.h"
#include "Action.h"
#include "MuffinRecipe.h"

class Scene
{
public:

	// constructors & destructors

	Scene() {};
	~Scene() {};

	// important functions

	virtual void init(sf::RenderWindow* _RenderWindow, sf::VideoMode* _videoMode) = 0;
	virtual void update(float dtime, sf::Event* event) = 0;
	virtual void render() = 0;

	// other functions

	virtual const char* getTitle() { return ""; };
	virtual void setTitle(const char* _cTitle) = 0;

};

#endif