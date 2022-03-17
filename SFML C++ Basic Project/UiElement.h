#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "pch.h"

/*
	Abstract Template Class
	detects onClick
*/
class UiElement
{
public:
	UiElement() {};
	virtual ~UiElement() = 0;

	virtual void init(sf::RenderWindow* _window) = 0;
	virtual void update(sf::Event* event) = 0;
	virtual void render() = 0;

	virtual const char* getTitle() { return ""; };
	virtual void setTitle(const char* _uiElementTitle) = 0;
	virtual void onClick() = 0;

};

#endif