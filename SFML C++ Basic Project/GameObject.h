#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "pch.h"

/*
	pretty much just an sfml sprite
	- init()
	- update()
	- render()
	- setTexture()
	- setPosition() / translate()
	- setRotation() / rotate()
	- setScale() / scale()
	- getSize() / getBoundingBox()
	- resetOrigin()
*/
class GameObject
{
private:

	// private variables
	//-------------------

	sf::RenderWindow* m_RenderWindow;
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
	sf::Image m_iDefaultImage;

public:

	// Constructors and Destructors
	//------------------------------

	GameObject();
	~GameObject();


	// basic
	//-------

	void init(sf::RenderWindow* _renderWindow, sf::Color _color, unsigned int _iWidth, unsigned int _iHeight);
	void init(sf::RenderWindow* _renderWindow, const char* _cFileName, unsigned int _iWidth, unsigned int _iHeight, bool _bRepeated);
	void update(sf::Event* event, float _fDeltaTime);
	void render();


	// sprite
	//--------

	void setTexture(sf::Color _color, unsigned int _iWidth, unsigned int _iHeight);
	void setTexture(const char* _cFileName, unsigned int _iWidth, unsigned int _iHeight, bool _bRepeated);


	// translate
	//-----------

	void setPosition(sf::Vector2f _position); 
	void translate(sf::Vector2f _moveAmount); 
	sf::Vector2f getPosition(); 


	// rotate	
	//--------

	void setRotation(float _rotation); 
	void rotate(float _rotationAmount); 
	float getRotation(); 


	// scale
	//-------

	void setScale(sf::Vector2f _scale); 
	void scale(sf::Vector2f _scaleAmount);
	sf::Vector2f getScale(); 


	// size
	//------

	sf::FloatRect getBoundingBox();
	sf::Vector2f getSize(); 
	

	// origin
	//--------

	void setOriginToCenter();
	void setOriginToTopLeft();
	void setOriginToBottomLeft();
	void setOriginToTopRight();
	void setOriginToBottomRight();
	sf::Vector2f getOrigin();

};

#endif