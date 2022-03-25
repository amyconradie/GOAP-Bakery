#include "GameObject.h"

GameObject::GameObject()
{
	this->m_RenderWindow = nullptr;
}

GameObject::~GameObject(){}

// init for game objects using solid colours
void GameObject::init(sf::RenderWindow* _renderWindow, sf::Color _color, unsigned int _iWidth, unsigned int _iHeight)
{
	this->m_RenderWindow = _renderWindow;
	setTexture(_color, _iWidth, _iHeight);
}

// init for game objects using images
void GameObject::init(sf::RenderWindow* _renderWindow, const char* _cFileName, unsigned int _iWidth, unsigned int _iHeight, bool _bRepeated)
{
	this->m_RenderWindow = _renderWindow;
	setTexture(_cFileName, _iWidth, _iHeight, _bRepeated);
}

void GameObject::update(sf::Event* event, float _fDeltaTime)
{
	// update things?
}

void GameObject::render()
{
	this->m_RenderWindow->draw(this->m_Sprite);
}

// set sprite texture as fill colour
void GameObject::setTexture(sf::Color _color, unsigned int _iWidth, unsigned int _iHeight )
{
	this->m_iDefaultImage.create(_iWidth, _iHeight, _color); // fill
	this->m_Texture.loadFromImage(this->m_iDefaultImage);
	this->m_Texture.setSmooth(true);
	this->m_Sprite.setTexture(this->m_Texture);
}

// set sprite texture as given fileName
void GameObject::setTexture(const char* _cFileName, unsigned int _iWidth, unsigned int _iHeight, bool _bRepeated)
{
	// load image from files (make sure to include file extension e.g. '.png')
	if (!this->m_Texture.loadFromFile(_cFileName))
	{
		std::cout << "No file loaded: " << _cFileName << "\n";
	}

	this->m_Texture.setSmooth(true); // aliasing i think? looks weird without it
	this->m_Sprite.setTexture(this->m_Texture);

	// if _bRepeated = true make image tileable
	if (_bRepeated)
	{
		this->m_Sprite.setScale(_iWidth / this->m_Sprite.getLocalBounds().width, _iHeight / this->m_Sprite.getLocalBounds().height); // set sprite to requested size
		this->m_Texture.setRepeated(true);
		this->m_Sprite.setTextureRect( // this is what makes sure the tiles stretch to fight the window
			sf::IntRect(
				0.f, 
				0.f, 
				sf::VideoMode::getDesktopMode().width / this->m_Sprite.getScale().x, // makes sure tiles stretch to window edges if images are set to small size
				sf::VideoMode::getDesktopMode().height / this->m_Sprite.getScale().y // ^^^
			)
		);
	}
	else 
	{
		this->m_Sprite.setScale(_iWidth / this->m_Sprite.getLocalBounds().width, _iHeight / this->m_Sprite.getLocalBounds().height); // set sprite to requested size
	}
}

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

// returns sprite origin
sf::Vector2f GameObject::getOrigin()
{
	return this->m_Sprite.getOrigin();
}
