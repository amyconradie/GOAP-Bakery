#include "GameObject.h"


// Constructors and Destructors
//------------------------------

GameObject::GameObject()
{
	this->m_RenderWindow = nullptr;
}

GameObject::~GameObject()
{

}





// important 
//-----------

void GameObject::init(sf::RenderWindow* _renderWindow, unsigned int _iWidth, unsigned int _iHeight, sf::Color _color)
{
	this->m_RenderWindow = _renderWindow;
	setTexture(_iWidth, _iHeight, _color);
}

//void GameObject::init(sf::RenderWindow* _renderWindow, unsigned int _iWidth, unsigned int _iHeight, sf::Color _cTopLeft, sf::Color _cTopRight, sf::Color _cBottomLeft, sf::Color _cBottomRight, bool _bRepeated)
//{
//	this->m_RenderWindow = _renderWindow;
//	setTexture(_iWidth, _iHeight, _cTopLeft, _cTopRight, _cBottomLeft, _cBottomRight, _bRepeated);
//}

void GameObject::init(sf::RenderWindow* _renderWindow, const char* _cFileName, unsigned int _iWidth, unsigned int _iHeight,  bool _bRepeated)
{
	this->m_RenderWindow = _renderWindow;
	setTexture(_cFileName, _iWidth, _iHeight, _bRepeated);
}

void GameObject::update(sf::Event* event, float _fDeltaTime)
{

}

void GameObject::render()
{
	this->m_RenderWindow->draw(this->m_Sprite);
}



// sprite
//--------

// set as fill colour
void GameObject::setTexture(unsigned int _iWidth, unsigned int _iHeight, sf::Color _color)
{
	this->m_iDefaultImage.create(_iWidth, _iHeight, _color); // fill
	this->m_Texture.loadFromImage(this->m_iDefaultImage);
	this->m_Texture.setSmooth(true);
	this->m_Sprite.setTexture(this->m_Texture);
}

//// HOW????
//// set as gradient colour
//void GameObject::setTexture(unsigned int _iWidth, unsigned int _iHeight, sf::Color _cTopLeft, sf::Color _cTopRight, sf::Color _cBottomLeft, sf::Color _cBottomRight, bool _bRepeated)
//{
//	this->m_iDefaultImage.create(_iWidth, _iHeight);
//	
//	//for (int x = 0; x < _iWidth; x++) {
//	//	for (int y = 0; y < _iHeight; y++) {
//	//		this->m_iDefaultImage.setPixel(x, y, sf::Color(random(255), random(255), random(255)));
//	//	}
//	//}
//
//	//sf::Vertex vCorners[] = {
//	//	sf::Vertex(sf::Vector2f(0, 0), _cTopLeft),
//	//	sf::Vertex(sf::Vector2f(_iWidth, 0), _cTopRight),
//	//	sf::Vertex(sf::Vector2f(0, _iHeight), _cBottomLeft),
//	//	sf::Vertex(sf::Vector2f(_iWidth, _iHeight), _cBottomRight)
//	//};
//
//	//sf::VertexArray tempRect(sf::Quads, 4);
//	//tempRect[0].position = sf::Vector2f(0, 0);
//	//tempRect[0].color = _cTopLeft;
//	//tempRect[1].position = sf::Vector2f(_iWidth, 0);
//	//tempRect[1].color = _cTopRight;
//	//tempRect[2].position = sf::Vector2f(0, _iHeight);
//	//tempRect[2].color = _cBottomLeft;
//	//tempRect[3].position = sf::Vector2f(_iWidth, _iHeight);
//	//tempRect[3].color = _cBottomRight;
//
//	////std::vector<sf::RectangleShape> pixels;
//	////pixels.push_back(addPixel({ 100, 100 }, 255, 0, 0));
//	////pixels.push_back(addPixel({ 101, 100 }, 255, 255, 0));
//	////pixels.push_back(addPixel({ 102, 100 }, 0, 0, 0));
//	////pixels.push_back(addPixel({ 103, 100 }, 255, 0, 255));
//
//	////sf::Image tempRectImage;
//	////tempRectImage.create(_iWidth, _iHeight);
//	////tempRect.
//
//	//sf::RenderTexture renTex;
//	//renTex.getTexture();
//
//	this->m_Texture.loadFromImage(this->m_iDefaultImage);
//	this->m_Texture.setSmooth(true);
//	this->m_Sprite.setTexture(this->m_Texture);
//
//	if (_bRepeated)
//	{
//		this->m_Texture.setRepeated(true);
//		this->m_Sprite.setTextureRect(sf::IntRect(0.f, 0.f, _iWidth, _iHeight));
//	}
//}

// If fileName not given, use the size
void GameObject::setTexture(const char* _cFileName, unsigned int _iWidth, unsigned int _iHeight, bool _bRepeated)
{
	if (!this->m_Texture.loadFromFile(_cFileName))
	{
		std::cout << "No file loaded: " << _cFileName << "\n";
	}

	this->m_Texture.setSmooth(true);
	this->m_Sprite.setTexture(this->m_Texture);

	if (_bRepeated)
	{
		this->m_Texture.setRepeated(true);
		this->m_Sprite.setTextureRect(sf::IntRect(0.f, 0.f, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	}
	else 
	{
		this->m_Sprite.setScale(_iWidth / this->m_Sprite.getLocalBounds().width, _iHeight / this->m_Sprite.getLocalBounds().height);
	}
}



// translate
//-----------

// set absolute position
void GameObject::setPosition(sf::Vector2f _position) 
{ 
	this->m_Sprite.setPosition(_position); 
};

// translate by xy amounts
void GameObject::translate(sf::Vector2f _moveAmount) 
{ 
	this->m_Sprite.move(_moveAmount); 
};

// returns current position
sf::Vector2f GameObject::getPosition() 
{ 
	return this->m_Sprite.getPosition(); 
};





// rotate	
//--------

// set absolute rotation
void GameObject::setRotation(float _rotation) 
{ 
	this->m_Sprite.setRotation(_rotation); 
};

// rotate by float amount
void GameObject::rotate(float _rotationAmount) 
{ 
	this->m_Sprite.rotate(_rotationAmount); 
};

// return current rotation amount
float GameObject::getRotation() 
{ 
	return this->m_Sprite.getRotation(); 
};





// scale
//-------

// set absolute scale
void GameObject::setScale(sf::Vector2f _scale) 
{ 
	this->m_Sprite.setScale(_scale); 
};

// scale by xy float amounts
void GameObject::scale(sf::Vector2f _scaleAmount) 
{ 
	this->m_Sprite.scale(_scaleAmount); 
};

// return current scale amount
sf::Vector2f GameObject::getScale() 
{ 
	return this->m_Sprite.getScale(); 
};





// size
//------

// takes into account any transformations that have been applied
sf::FloatRect GameObject::getBoundingBox() 
{ 
	return this->m_Sprite.getGlobalBounds(); 
};

// is this any different from getGlobalBounds()??
sf::Vector2f GameObject::getSize() 
{ 
	return sf::Vector2f(this->m_Sprite.getLocalBounds().width* m_Sprite.getScale().x, this->m_Sprite.getLocalBounds().height * m_Sprite.getScale().y);
}; 






// origin
//--------

// set origin to center
void GameObject::setOriginToCenter() 
{ 
	this->m_Sprite.setOrigin(sf::Vector2f(this->getBoundingBox().width / 2, this->getBoundingBox().height / 2));
};

// set origin to top left
void GameObject::setOriginToTopLeft() 
{ 
	this->m_Sprite.setOrigin(sf::Vector2f(this->getBoundingBox().left, this->getBoundingBox().top)); 
};

// set origin to bottom left
void GameObject::setOriginToBottomLeft() 
{ 
	this->m_Sprite.setOrigin(sf::Vector2f(this->getBoundingBox().left, this->getBoundingBox().height));
};

// set origin to top right
void GameObject::setOriginToTopRight() 
{ 
	this->m_Sprite.setOrigin(sf::Vector2f(this->getBoundingBox().width, this->getBoundingBox().top));
};

// set origin to bottom right
void GameObject::setOriginToBottomRight() 
{ 
	this->m_Sprite.setOrigin(sf::Vector2f(this->getBoundingBox().width, this->getBoundingBox().height));
}

sf::Vector2f GameObject::getOrigin()
{
	return this->m_Sprite.getOrigin();
}
;