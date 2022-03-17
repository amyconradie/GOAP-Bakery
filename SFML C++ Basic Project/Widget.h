//#ifndef WIDGET_H
//#define WIDGET_H
//
//#include "pch.h"
//#include "UiElement.h"
//
///*
//	Dynamically Resizes based on size and number of UiElements
//*/
//class Widget
//{
//private:
//
//	sf::RenderWindow* m_RenderWindow;
//	const char* m_cTitle = "";
//	std::vector<UiElement*> m_UiElements;
//
//public:
//
//	// Constructors and Destructors
//	//------------------------------
//
//	Widget();
//	~Widget();
//
//
//	// setup functions
//	//-----------------
//
//	void init(sf::RenderWindow* _window);
//	void update(sf::Event* event);
//	void render();
//
//	const char* getTitle() { return this->m_cTitle; };
//	void setTitle(const char* _title) { m_cTitle = _title; };
//	void onClick();
//};
//
//#endif