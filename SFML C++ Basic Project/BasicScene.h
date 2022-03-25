#ifndef BASICSCENE_H
#define BASICSCENE_H

#include "pch.h"
#include "Scene.h"

class BasicScene 
	: public Scene
{
private:

	// private variables
	//-------------------

	sf::RenderWindow* m_RenderWindow;
	const char* m_cTitle;
	sf::Vector2i m_v2iMousePosWindow;
	sf::Vector2f m_v2fMousePosView;
	std::vector<GameObject*> m_vgGameObjects;
	sf::Shader m_sCoreShader;

public:

	// constructors & destructors
	//----------------------------

	BasicScene();
	~BasicScene();


	// important functions
	//---------------------

	virtual void init(sf::RenderWindow* _RenderWindow);
	virtual void update(float _fDeltaTime, sf::Event* event);
	virtual void render();


	// other functions
	//-----------------

	virtual const char* getTitle();
	virtual void setTitle(const char* _cTitle);
	virtual void updateMousePositions(float _fDeltaTime);
};

#endif