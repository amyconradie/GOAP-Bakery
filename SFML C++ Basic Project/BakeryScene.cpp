#include "BakeryScene.h"

BakeryScene::BakeryScene()
{
	this->m_RenderWindow = nullptr;
	this->m_VideoMode = nullptr;
	this->m_cTitle = "";
	this->currentWorldState = nullptr;
	this->m_textBox = nullptr;
	this->m_nextStepsTextBox = nullptr;
}

BakeryScene::~BakeryScene()
{
	// makes sure any pointers are deleted when the scene is destroyed
	for (auto& gameObject : this->m_vGameObjects)
		delete gameObject;

	delete m_MuffinRecipe;
	delete m_textBox;
	delete m_nextStepsTextBox;
}

// pretty much the entire setup for the scene should go in here
// pretty much the entire setup for the scene should go in here
void BakeryScene::init(sf::RenderWindow* _window, sf::VideoMode* _videoMode)
{
	this->m_RenderWindow = _window;
	this->m_VideoMode = _videoMode;

	// create and set view
	this->m_RenderWindow->setView(
		calcView(
			m_RenderWindow->getSize(),
			sf::Vector2f(
				sf::VideoMode::getDesktopMode().width,
				sf::VideoMode::getDesktopMode().height
			)
		)
	);

	// store current window size for future use in the MaintainAspectRatio() function
	this->m_v2uOldWindowSize = this->m_RenderWindow->getSize();

	this->m_RenderWindow = _window;
	updateMousePositions(1);

	// set window icon
	sf::Image icon;
	icon.loadFromFile("Images\\muffin.png");
	this->m_RenderWindow->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// create background
	CreateGameObject(sf::Color(76, 47, 99), this->m_RenderWindow->getSize().x, this->m_RenderWindow->getSize().y, 0, 0);

	this->width = this->m_RenderWindow->getSize().x;
	this->height = this->m_RenderWindow->getSize().y;
	this->blockWidth = width / 5;
	this->blockHeight = height / 3;

	// floor pattern

	sf::Color tileColour1 = sf::Color(125, 125, 125);//sf::Color(110, 70, 130)
	sf::Color tileColour2 = sf::Color(105, 105, 105);//sf::Color(90, 60, 120)

	GameObject* a1 = CreateGameObject(sf::Color(tileColour1), blockWidth, blockHeight, 0, 0);
	GameObject* a2 = CreateGameObject(sf::Color(tileColour2), blockWidth, blockHeight, blockWidth, 0);
	GameObject* a3 = CreateGameObject(sf::Color(tileColour1), blockWidth, blockHeight, blockWidth * 2, 0);
	GameObject* a4 = CreateGameObject(sf::Color(tileColour2), blockWidth, blockHeight, blockWidth * 3, 0);
	GameObject* a5 = CreateGameObject(sf::Color(tileColour1), blockWidth, blockHeight, blockWidth * 4, 0);
	GameObject* b1 = CreateGameObject(sf::Color(tileColour2), blockWidth, blockHeight, 0, blockHeight);
	GameObject* b2 = CreateGameObject(sf::Color(tileColour1), blockWidth, blockHeight, blockWidth, blockHeight);
	GameObject* b3 = CreateGameObject(sf::Color(tileColour2), blockWidth, blockHeight, blockWidth * 2, blockHeight);
	GameObject* b4 = CreateGameObject(sf::Color(tileColour1), blockWidth, blockHeight, blockWidth * 3, blockHeight);
	GameObject* b5 = CreateGameObject(sf::Color(tileColour2), blockWidth, blockHeight, blockWidth * 4, blockHeight);
	GameObject* c1 = CreateGameObject(sf::Color(tileColour1), blockWidth, blockHeight, 0, blockHeight * 2);
	GameObject* c2 = CreateGameObject(sf::Color(tileColour2), blockWidth, blockHeight, blockWidth, blockHeight * 2);
	GameObject* c3 = CreateGameObject(sf::Color(tileColour1), blockWidth, blockHeight, blockWidth * 2, blockHeight * 2);
	GameObject* c4 = CreateGameObject(sf::Color(tileColour2), blockWidth, blockHeight, blockWidth * 3, blockHeight * 2);
	GameObject* c5 = CreateGameObject(sf::Color(tileColour1), blockWidth, blockHeight, blockWidth * 4, blockHeight * 2);

	// add oven
	gOven = CreateGameObject("images\\oven_closed.png", false, blockWidth, blockHeight, 0, 0);
	gOven->setPosition(
		sf::Vector2f(
			0,
			0
		)
	);

	// add mixer
	gMixer = CreateGameObject("images\\whisk_off.png", false, blockWidth, blockHeight, 0, 0);
	gMixer->setPosition(
		sf::Vector2f(
			blockWidth,
			0
		)
	);

	// add pantry
	gPantry = CreateGameObject("images\\pantry_closed.png", false, blockWidth, blockHeight, 0, 0);
	gPantry->setPosition(
		sf::Vector2f(
			blockWidth * 2,
			0
		)
	);

	// add sink
	gSink = CreateGameObject("images\\sink_tap_off.png", false, blockWidth, blockHeight, 0, 0);
	gSink->setPosition(
		sf::Vector2f(
			0,
			blockHeight * 2
		)
	);

	// add fridge
	gFridge = CreateGameObject("Images\\fridge_closed.png", false, blockWidth, blockHeight, 0, 0);
	gFridge->setPosition(
		sf::Vector2f(
			blockWidth,
			blockHeight * 2
		)
	);

	// add cooling rack
	gCoolRack = CreateGameObject("Images\\rack.png", false, blockWidth, blockHeight, 0, 0);
	gCoolRack->setPosition(
		sf::Vector2f(
			blockWidth * 2,
			blockHeight * 2
		)
	);

	// add displayCases
	gDisplayCase1 = CreateGameObject("Images\\empty_display.png", false, blockWidth, blockHeight, 0, 0);
	gDisplayCase1->setPosition(
		sf::Vector2f(
			blockWidth * 4,
			0
		)
	);

	// add displayCases
	gDisplayCase2 = CreateGameObject("Images\\empty_display.png", false, blockWidth, blockHeight, 0, 0);
	gDisplayCase2->setPosition(
		sf::Vector2f(
			blockWidth * 4,
			blockHeight
		)
	);

	// add displayCases
	gDisplayCase3 = CreateGameObject("Images\\empty_display.png", false, blockWidth, blockHeight, 0, 0);
	gDisplayCase3->setPosition(
		sf::Vector2f(
			blockWidth * 4,
			blockHeight * 2
		)
	);


	// create the agent last so it's easy to find again
	gBaker = CreateGameObject("Images\\baker.png", false, blockWidth, blockHeight, blockWidth * 2, blockHeight);
	gBaker->setPosition(
		sf::Vector2f(
			blockWidth * 2,
			blockHeight
		)
	);

	// positions infront of each position

	m_iOvenPos = sf::Vector2f(
		0,
		1 * blockHeight
	);

	m_iMixerPos = sf::Vector2f(
		1 * blockWidth,
		1 * blockHeight
	);

	m_iPantryPos = sf::Vector2f(
		2 * blockWidth,
		1 * blockHeight
	);

	m_iSinkPos = sf::Vector2f(
		0,
		1 * blockHeight
	);

	m_iFridgePos = sf::Vector2f(
		1 * blockWidth,
		1 * blockHeight
	);

	m_iCoolingRackPos = sf::Vector2f(
		2 * blockWidth,
		1 * blockHeight
	);

	m_iDisplayCase1Pos = sf::Vector2f(
		3 * blockWidth,
		0
	);

	m_iDisplayCase2Pos = sf::Vector2f(
		3 * blockWidth,
		1 * blockHeight
	);

	m_iDisplayCase3Pos = sf::Vector2f(
		3 * blockWidth,
		2 * blockHeight
	);

	sf::Font font;
	m_font.loadFromFile("Fonts\\PatuaOne-Regular.ttf");

	this->m_textBox = new sf::Text("", m_font);
	this->m_textBox->setCharacterSize(100);
	this->m_textBox->setStyle(sf::Text::Bold);
	this->m_textBox->setFillColor(sf::Color(55, 55, 55, 150));
	this->m_textBox->setPosition(blockWidth * 0.05, blockHeight * 0.98); // set to top-middle right

	this->m_nextStepsTextBox = new sf::Text("", m_font);
	this->m_nextStepsTextBox->setCharacterSize(40);
	this->m_nextStepsTextBox->setStyle(sf::Text::Regular);
	this->m_nextStepsTextBox->setFillColor(sf::Color(55, 55, 55, 80));
	this->m_nextStepsTextBox->setPosition((blockWidth * 3) + (blockWidth * 0.05), height * 0.01); // set to top right

	this->m_MuffinRecipe = new MuffinRecipe();

	this->m_bCoolingRack1Full = false;
	this->m_bCoolingRack2Full = false;
	this->m_bCoolingRack3Full = false;

	this->m_iDisplayCase1MuffinCount = 0;
	this->m_iDisplayCase2MuffinCount = 0;
	this->m_iDisplayCase3MuffinCount = 0;

	UpdateRecipe();
}

void BakeryScene::UpdateRecipe() {
	this->m_vaRecipe = this->m_MuffinRecipe->GetMuffinRecipe();

	if (!this->m_vsTaskNames.empty()) {
		this->m_vsTaskNames.clear(); // make sure to empty task names list
	}

	if (!this->m_vaRecipe.empty()) {
		this->m_sCurrentTask = this->m_vaRecipe.front().getName();

		for (auto& action : this->m_vaRecipe) {
			m_vsTaskNames.push_back(action.getName());
		}

		// so that I can have the action name show up before the action
		Action buffer_action("", 0);
		this->m_vaRecipe.insert(this->m_vaRecipe.begin(), buffer_action);

		m_vsTaskNames.push_back("wait for next goal");

		//std::cout << "Make Muffins:\n";
		//int i = 0;
		//for (auto& step : this->m_vaRecipe) {
		//	std::cout << step.getName() << ", cost: " << step.getCost() << "\n";
		//	i += step.getCost();
		//}
		//std::cout << "Total Cost: " << i << "\n";

	}
	else {
		this->m_sCurrentTask = "";
	}
}

// updates the scene
// - updates mouse click positions
void BakeryScene::update(float _fDeltaTime, sf::Event* _event)
{
	while (this->m_RenderWindow->pollEvent(*_event))
	{
		switch (_event->type)
		{

			// If "close"/"x" button is pressed, close the game/app
		case sf::Event::Closed:
			this->m_RenderWindow->close();
			break;

			// If Screen is Resized maintain the aspect ratio
		case sf::Event::Resized:
			MaintainAspectRatio(true);
			break;

			// detect mouse clicks when released
		case sf::Event::MouseButtonReleased:
			if (_event->mouseButton.button == sf::Mouse::Left)
			{
				updateMousePositions(_fDeltaTime); // prevents repeat clicks too quickly
				sf::Vector2i v2iTempMPW = sf::Mouse::getPosition(*this->m_RenderWindow);
				std::cout << "mouse window position: x:" << v2iTempMPW.x << ", y:" << v2iTempMPW.y << "\n";
				sf::Vector2f v2fTempMPV = this->m_RenderWindow->mapPixelToCoords(v2iTempMPW);
				std::cout << "mouse view   position: x:" << v2fTempMPV.x << ", y:" << v2fTempMPV.y << "\n";
			}
			break;

			// for key presses that cannot be held down
		case sf::Event::KeyReleased:
			this->m_RenderWindow->setKeyRepeatEnabled(false);

			// If "Esc" key is pressed, close the game/app
			if (_event->key.code == sf::Keyboard::Escape)
			{
				this->m_RenderWindow->close();
			}

			break;

			// for key presses that can be held down
		case sf::Event::KeyPressed:
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)) && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				this->toggleFullscreen();
			}
			break;

			// all other events
		default:
			break;
		}
	}
	
	UpdateText();

	performNextTaskTimer += _fDeltaTime;
	decreaseMuffinsTimer += _fDeltaTime;

	if (performNextTaskTimer > 0.5f)
	{
		Sleep(500);
		UpdateTasks();
		performNextTaskTimer = 0;

		if (decreaseMuffinsTimer > 1.f) {
			DecreaseMuffins();
			decreaseMuffinsTimer = 0;
		}
	}
}

// draws all the drawable objects in the scene
void BakeryScene::render()
{

	// renders objects in the order they were added
	for (auto& gameObject : m_vGameObjects)
	{
		gameObject->render();
	}

	// render text 
	this->m_RenderWindow->draw(*m_textBox);
	this->m_RenderWindow->draw(*m_nextStepsTextBox);
}

//	creates a new view with the correct size based on a given aspect ratio
sf::View BakeryScene::calcView(sf::Vector2u _v2uWindowSize, sf::Vector2f _v2fDesignedSize)
{
	sf::FloatRect viewport(0.f, 0.f, 1.f, 1.f);

	float screenwidth = _v2uWindowSize.x / static_cast<float>(_v2fDesignedSize.x);
	float screenheight = _v2uWindowSize.y / static_cast<float>(_v2fDesignedSize.y);

	if (screenwidth > screenheight)
	{
		viewport.width = screenheight / screenwidth;
		viewport.left = (1.f - viewport.width) / 2.f;
	}
	else if (screenwidth < screenheight)
	{
		viewport.height = screenwidth / screenheight;
		viewport.top = (1.f - viewport.height) / 2.f;
	}

	sf::View view(sf::FloatRect(0, 0, _v2fDesignedSize.x, _v2fDesignedSize.y));
	view.setViewport(viewport);

	return view;
}

// rescales window to match viewport size
// calls calcView to determine the appropriate aspectRatio based on the user's monitor
void BakeryScene::MaintainAspectRatio(bool _bRescaleWindow)
{
	// creates black letterboxing
	// makes sure aspect ratio is not distorted by adding black letterboxing
	// create new view
	this->m_RenderWindow->setView(
		calcView(
			m_RenderWindow->getSize(),
			sf::Vector2f(
				sf::VideoMode::getDesktopMode().width,
				sf::VideoMode::getDesktopMode().height
			)
		)
	);

	if (_bRescaleWindow)
	{
		float wProportions = 0;
		float hProportions = 0;
		float newWidth = this->m_RenderWindow->getSize().x;
		float newHeight = this->m_RenderWindow->getSize().y;
		float newPosLeft = this->m_RenderWindow->getPosition().x;
		float newPosTop = this->m_RenderWindow->getPosition().y;

		// height is larger than it should be
		// window width was decreased
		// make height smaller to match
		if (this->m_v2uOldWindowSize.x > this->m_RenderWindow->getSize().x)
		{
			hProportions = this->m_RenderWindow->getView().getViewport().top * 2;
			newHeight = this->m_RenderWindow->getSize().y - (this->m_RenderWindow->getSize().y * hProportions);
		}

		// width is larger than it should be
		// window height was decreased
		// make width smaller to match
		if (this->m_v2uOldWindowSize.y > this->m_RenderWindow->getSize().y)
		{
			wProportions = this->m_RenderWindow->getView().getViewport().left * 2;
			newWidth = this->m_RenderWindow->getSize().x - (this->m_RenderWindow->getSize().x * wProportions);
		}

		/*
			!!! ALERT !!!
			- this part only kind of works
			- increasing window size seems to keep letterboxing when it shouldn't
			- unsure what conditions to set when scaling window up
		*/

		double widthRatio = (double)this->m_v2uOldWindowSize.x / sf::VideoMode::getDesktopMode().width;
		double heightRatio = (double)this->m_v2uOldWindowSize.y / sf::VideoMode::getDesktopMode().height;

		// width is smaller than it should be
		// window height was increased
		// make width larger to match
		if (this->m_v2uOldWindowSize.y < this->m_RenderWindow->getSize().y)
		{
			wProportions = this->m_RenderWindow->getView().getViewport().width;
			newWidth = this->m_RenderWindow->getSize().x * wProportions;
		}

		// height is smaller than it should be
		// window width was increased
		// make height larger to match
		if (this->m_v2uOldWindowSize.x < this->m_RenderWindow->getSize().x)
		{
			hProportions = this->m_RenderWindow->getView().getViewport().height;
			newHeight = this->m_RenderWindow->getSize().y * hProportions;
		}

		// implement changes to window
		this->m_RenderWindow->setSize(
			sf::Vector2u(
				round(newWidth),
				round(newHeight)
			)
		);

		// store new window size, for future reference
		this->m_v2uOldWindowSize = this->m_RenderWindow->getSize();
	}
}

// on "alt + enter" switch between windowedand fullscreen modes
void BakeryScene::toggleFullscreen()
{
	if (this->m_bToggle)
	{
		// create windowed screen
		*m_VideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
		this->m_RenderWindow->create(
			*m_VideoMode,
			m_cTitle,
			sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close
		);

		// set window size to 75% of fullscreen
		this->m_RenderWindow->setSize(
			sf::Vector2u(
				this->m_VideoMode->width * 0.75,
				this->m_VideoMode->height * 0.75
			)
		);

		// set window position to the center of the monitor
		this->m_RenderWindow->setPosition(
			sf::Vector2i(
				(sf::VideoMode::getDesktopMode().width - this->m_RenderWindow->getSize().x) * 0.4,
				(sf::VideoMode::getDesktopMode().height - this->m_RenderWindow->getSize().y) * 0.4
			)
		);
	}
	else
	{
		// create fullscreen
		this->m_RenderWindow->create(*m_VideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), m_cTitle, sf::Style::Fullscreen);
	}

	// forces view to maintain the correct aspect ratio
	// and brute forces window size to match the view size
	MaintainAspectRatio(true);

	// switch toggle to opposite setting
	this->m_bToggle = !this->m_bToggle;
}

const char* BakeryScene::getTitle()
{
	return this->m_cTitle;
}

void BakeryScene::setTitle(const char* _sceneTitle)
{
	this->m_cTitle = _sceneTitle;
}

// compares doubles to see if they are the exact same value
bool areSame(double x, double y)
{
	return std::fabs(x - y) <= std::numeric_limits<double>::epsilon();
}

// stores when mousePosition Changes
// makes sure click isnt registered multiple times
// if it's too close in time to the previous click 
// or it's in the exact same place
void BakeryScene::updateMousePositions(float _fDeltaTime)
{
	sf::Vector2i v2iTempMPW = sf::Mouse::getPosition(*this->m_RenderWindow);
	sf::Vector2f v2fTempMPV = this->m_RenderWindow->mapPixelToCoords(this->m_v2iMousePosWindow);

	float _fTimeBtwnClicks = 0.01;

	if (!areSame(this->m_v2iMousePosWindow.x, v2iTempMPW.x) || _fDeltaTime > _fTimeBtwnClicks)
		this->m_v2iMousePosWindow.x = v2iTempMPW.x;

	if (!areSame(this->m_v2iMousePosWindow.y, v2iTempMPW.y) || _fDeltaTime > _fTimeBtwnClicks)
		this->m_v2iMousePosWindow.y = v2iTempMPW.y;

	if (!areSame(this->m_v2fMousePosView.x, v2fTempMPV.x) || _fDeltaTime > _fTimeBtwnClicks)
		this->m_v2fMousePosView.x = v2fTempMPV.x;

	if (!areSame(this->m_v2fMousePosView.y, v2fTempMPV.y) || _fDeltaTime > _fTimeBtwnClicks)
		this->m_v2fMousePosView.y = v2fTempMPV.y;
}


GameObject* BakeryScene::CreateGameObject(sf::Color _color, unsigned int _width, unsigned int _height, unsigned int _xpos, unsigned int _ypos)
{
	GameObject* gameObject = new GameObject;
	gameObject->init(this->m_RenderWindow, _color, _width, _height);
	gameObject->setOriginToTopLeft();
	gameObject->setPosition(sf::Vector2f(_xpos, _ypos));
	m_vGameObjects.push_back(gameObject);

	return gameObject;
}

GameObject* BakeryScene::CreateGameObject(const char* _cFileName, bool _bRepeat, unsigned int _width, unsigned int _height, unsigned int _xpos, unsigned int _ypos)
{
	GameObject* gameObject = new GameObject;

	if (_bRepeat)
	{
		gameObject->init(this->m_RenderWindow, _cFileName, _width, _height, true);
	}
	else {
		gameObject->init(this->m_RenderWindow, _cFileName, _width, _height, false);
	}

	gameObject->setOriginToTopLeft();
	gameObject->setPosition(sf::Vector2f(_xpos, _ypos));
	m_vGameObjects.push_back(gameObject);

	return gameObject;
}

State BakeryScene::PerformActionsOnState(std::vector<Action> _actions, State _initialState)
{
	State tempState = _initialState;

	for (auto& action : _actions) {
		tempState = action.performOnState(tempState);
	}

	return tempState;
}

void BakeryScene::OpenPantry()
{
	gPantry->setTexture("Images\\pantry_open.png", this->blockWidth, this->blockHeight, false);
	this->m_sCurrentTask = m_c_open_pantry;
}

void BakeryScene::ClosePantry()
{
	gPantry->setTexture("Images\\pantry_closed.png", this->blockWidth, this->blockHeight, false);
	this->m_sCurrentTask = m_c_close_pantry;
}

void BakeryScene::OpenFridge()
{
	gFridge->setTexture("Images\\fridge_open.png", this->blockWidth, this->blockHeight, false);
	this->m_sCurrentTask = m_c_open_fridge;
}

void BakeryScene::CloseFridge()
{
	gFridge->setTexture("Images\\fridge_closed.png", this->blockWidth, this->blockHeight, false);
	this->m_sCurrentTask = m_c_close_fridge;
}

void BakeryScene::OpenOven()
{
	gOven->setTexture("Images\\oven_open.png", this->blockWidth, this->blockHeight, false);
	this->m_sCurrentTask = m_c_open_oven;
}

void BakeryScene::CloseOven()
{
	gOven->setTexture("Images\\oven_closed.png", this->blockWidth, this->blockHeight, false);
	this->m_sCurrentTask = m_c_close_oven;
}

void BakeryScene::TurnOvenOff()
{
	this->m_sCurrentTask = m_c_turn_oven_off;
}

void BakeryScene::TurnOvenOn()
{
	this->m_sCurrentTask = m_c_turn_oven_on;
}

void BakeryScene::TurnSinkOff()
{
	gSink->setTexture("Images\\sink_tap_off.png", this->blockWidth, this->blockHeight, false);
	this->m_sCurrentTask = m_c_turn_sink_off;
}

void BakeryScene::TurnSinkOn()
{
	gSink->setTexture("Images\\sink_tap_on.png", this->blockWidth, this->blockHeight, false);
	this->m_sCurrentTask = m_c_turn_sink_on;
}

void BakeryScene::CleanMixer()
{
	gMixer->setTexture("Images\\whisk_off.png", this->blockWidth, this->blockHeight, false);
	this->m_sCurrentTask = m_c_clean_mixer;
}

void BakeryScene::CleanMuffinTray()
{
	this->m_sCurrentTask = m_c_clean_muffin_tray;
}

void BakeryScene::GetColdIngredients()
{
	this->m_sCurrentTask = m_c_get_cold_ingredients;
}

void BakeryScene::GetPantryIngredients()
{
	this->m_sCurrentTask = m_c_get_pantry_ingredients;
}

void BakeryScene::MixIngredients()
{
	gMixer->setTexture("Images\\whisk_on.png", this->blockWidth, this->blockHeight, false);
	this->m_sCurrentTask = m_c_mix_ingredients;
}

void BakeryScene::PourBatterIntoTray()
{
	gMixer->setTexture("Images\\whisk_off.png", this->blockWidth, this->blockHeight, false);
	this->m_sCurrentTask = m_c_pour_batter_into_tray;
}

void BakeryScene::PutMuffinTrayIntoOven()
{
	this->m_sCurrentTask = m_c_put_muffin_tray_into_oven;
}

void BakeryScene::BakeMuffins()
{
	this->m_sCurrentTask = m_c_bake_muffins;
}

void BakeryScene::RemoveMuffinTrayFromOven()
{
	this->m_sCurrentTask = m_c_remove_muffin_tray_from_oven;
}

void BakeryScene::MoveToCoolingRack()
{
	this->gBaker->setPosition(this->m_iCoolingRackPos);
	this->m_sCurrentTask = m_c_move_to_cooling_rack;
}

void BakeryScene::MoveToDisplayCase1()
{
	this->gBaker->setPosition(this->m_iDisplayCase1Pos);
	this->m_sCurrentTask = m_c_move_to_display_case_1;
}

void BakeryScene::MoveToDisplayCase2()
{
	this->gBaker->setPosition(this->m_iDisplayCase2Pos);
	this->m_sCurrentTask = m_c_move_to_display_case_2;
}

void BakeryScene::MoveToDisplayCase3()
{
	this->gBaker->setPosition(this->m_iDisplayCase3Pos);
	this->m_sCurrentTask = m_c_move_to_display_case_3;
}

void BakeryScene::MoveToFridge()
{
	this->gBaker->setPosition(this->m_iFridgePos);
	this->m_sCurrentTask = m_c_move_to_fridge;
}

void BakeryScene::MoveToMixer()
{
	this->gBaker->setPosition(this->m_iMixerPos);
	this->m_sCurrentTask = m_c_move_to_mixer;
}

void BakeryScene::MoveToOven()
{
	this->gBaker->setPosition(this->m_iOvenPos);
	this->m_sCurrentTask = m_c_move_to_oven;
}

void BakeryScene::MoveToPantry()
{
	this->gBaker->setPosition(this->m_iPantryPos);
	this->m_sCurrentTask = m_c_move_to_pantry;
}

void BakeryScene::MoveToSink()
{
	this->gBaker->setPosition(this->m_iSinkPos);
	this->m_sCurrentTask = m_c_move_to_sink;
}

void BakeryScene::PlaceMuffinsInDisplayCase1()
{
	//this->gBaker->setPosition(this->m_iDisplayCase1Pos);
	this->m_sCurrentTask = m_c_place_muffins_in_display_case_1;
	m_iDisplayCase1MuffinCount = 6;
	UpdateDisplayCase1();
}

void BakeryScene::PlaceMuffinsInDisplayCase2()
{
	//this->gBaker->setPosition(this->m_iDisplayCase2Pos);
	this->m_sCurrentTask = m_c_place_muffins_in_display_case_2;
	m_iDisplayCase2MuffinCount = 6;
	UpdateDisplayCase2();
}

void BakeryScene::PlaceMuffinsInDisplayCase3()
{
	//this->gBaker->setPosition(this->m_iDisplayCase3Pos);
	this->m_sCurrentTask = m_c_place_muffins_in_display_case_3;
	m_iDisplayCase3MuffinCount = 6;
	UpdateDisplayCase3();
}

void BakeryScene::DecreaseMuffins() 
{
	srand(time(NULL));
	int randNum = (rand() % 3) + 1;

	if (randNum == 1) 
	{
		RemoveAMuffinFromDisplayCase1();
	}

	if (randNum == 2) 
	{
		RemoveAMuffinFromDisplayCase2();
	}

	if (randNum == 3) 
	{
		RemoveAMuffinFromDisplayCase3();
	}
}

void BakeryScene::RemoveAMuffinFromDisplayCase1()
{
	//this->gBaker->setPosition(this->m_iDisplayCase1Pos);
	this->m_sCurrentTask = m_c_place_muffins_in_display_case_1;
	if (m_iDisplayCase1MuffinCount >= 0) {
		m_iDisplayCase1MuffinCount -= 1;
		std::cout << "number of muffins in display: " << m_iDisplayCase1MuffinCount << std::endl;
	}
	UpdateDisplayCase1();
}

void BakeryScene::RemoveAMuffinFromDisplayCase2()
{
	//this->gBaker->setPosition(this->m_iDisplayCase2Pos);
	this->m_sCurrentTask = m_c_place_muffins_in_display_case_2;
	if (m_iDisplayCase2MuffinCount >= 0) {
		m_iDisplayCase2MuffinCount - 1;
	}
	UpdateDisplayCase2();
}

void BakeryScene::RemoveAMuffinFromDisplayCase3()
{
	//this->gBaker->setPosition(this->m_iDisplayCase3Pos);
	this->m_sCurrentTask = m_c_place_muffins_in_display_case_3;
	if (m_iDisplayCase3MuffinCount > 0) {
		m_iDisplayCase3MuffinCount -= 1;
	}
	UpdateDisplayCase3();
}

void BakeryScene::UpdateDisplayCase1()
{
	switch (m_iDisplayCase1MuffinCount)
	{
	case 0:
		gDisplayCase1->setTexture("Images\\empty_display.png", this->blockWidth, this->blockHeight, false);
		break;
	case 1:
		gDisplayCase1->setTexture("Images\\display_1_muffin.png", this->blockWidth, this->blockHeight, false);
		break;
	case 2:
		gDisplayCase1->setTexture("Images\\display_2_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	case 3:
		gDisplayCase1->setTexture("Images\\display_3_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	case 4:
		gDisplayCase1->setTexture("Images\\display_4_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	case 5:
		gDisplayCase1->setTexture("Images\\display_5_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	case 6:
		gDisplayCase1->setTexture("Images\\display_6_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	default:
		break;
	}
}

void BakeryScene::UpdateDisplayCase2()
{
	switch (m_iDisplayCase2MuffinCount)
	{
	case 0:
		gDisplayCase2->setTexture("Images\\empty_display.png", this->blockWidth, this->blockHeight, false);
		break;
	case 1:
		gDisplayCase2->setTexture("Images\\display_1_muffin.png", this->blockWidth, this->blockHeight, false);
		break;
	case 2:
		gDisplayCase2->setTexture("Images\\display_2_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	case 3:
		gDisplayCase2->setTexture("Images\\display_3_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	case 4:
		gDisplayCase2->setTexture("Images\\display_4_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	case 5:
		gDisplayCase2->setTexture("Images\\display_5_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	case 6:
		gDisplayCase2->setTexture("Images\\display_6_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	default:
		break;
	}
}

void BakeryScene::UpdateDisplayCase3()
{
	switch (m_iDisplayCase3MuffinCount)
	{
	case 0:
		gDisplayCase3->setTexture("Images\\empty_display.png", this->blockWidth, this->blockHeight, false);
		break;
	case 1:
		gDisplayCase3->setTexture("Images\\display_1_muffin.png", this->blockWidth, this->blockHeight, false);
		break;
	case 2:
		gDisplayCase3->setTexture("Images\\display_2_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	case 3:
		gDisplayCase3->setTexture("Images\\display_3_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	case 4:
		gDisplayCase3->setTexture("Images\\display_4_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	case 5:
		gDisplayCase3->setTexture("Images\\display_5_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	case 6:
		gDisplayCase3->setTexture("Images\\display_6_muffins.png", this->blockWidth, this->blockHeight, false);
		break;
	default:
		break;
	}
}

void BakeryScene::PlaceMuffinsOnCoolingRack1()
{
	this->m_sCurrentTask = m_c_place_muffins_on_cooling_rack_1;
	m_bCoolingRack1Full = true;
	UpdateCoolingRack();
}

void BakeryScene::PlaceMuffinsOnCoolingRack2()
{
	this->m_sCurrentTask = m_c_place_muffins_on_cooling_rack_2;
	m_bCoolingRack2Full = true;
	UpdateCoolingRack();
}

void BakeryScene::PlaceMuffinsOnCoolingRack3()
{
	this->m_sCurrentTask = m_c_place_muffins_on_cooling_rack_3;
	m_bCoolingRack3Full = true; 
	UpdateCoolingRack();
}

void BakeryScene::RemoveMuffinsFromCoolingRack1()
{
	this->m_sCurrentTask = m_c_remove_muffins_from_cooling_rack_1;
	m_bCoolingRack3Full = false;
	UpdateCoolingRack();
}

void BakeryScene::RemoveMuffinsFromCoolingRack2()
{
	this->m_sCurrentTask = m_c_remove_muffins_from_cooling_rack_2;
	m_bCoolingRack3Full = false;
	UpdateCoolingRack();
}

void BakeryScene::RemoveMuffinsFromCoolingRack3()
{
	this->m_sCurrentTask = m_c_remove_muffins_from_cooling_rack_3;
	m_bCoolingRack3Full = false;
	UpdateCoolingRack();
}

void BakeryScene::UpdateCoolingRack()
{
	if (m_bCoolingRack1Full && m_bCoolingRack2Full && m_bCoolingRack3Full) {
		gCoolRack->setTexture("Images\\rack_1_2_3.png", this->blockWidth, this->blockHeight, false);
	}
	else if (m_bCoolingRack1Full && m_bCoolingRack2Full) {
		gCoolRack->setTexture("Images\\rack_1_2.png", this->blockWidth, this->blockHeight, false);
	}
	else if (m_bCoolingRack1Full && m_bCoolingRack3Full) {
		gCoolRack->setTexture("Images\\rack_1_3.png", this->blockWidth, this->blockHeight, false);
	}
	else if (m_bCoolingRack2Full && m_bCoolingRack3Full) {
		gCoolRack->setTexture("Images\\rack_2_3.png", this->blockWidth, this->blockHeight, false);
	}
	else if (m_bCoolingRack1Full) {
		gCoolRack->setTexture("Images\\rack_1.png", this->blockWidth, this->blockHeight, false);
	}
	else if (m_bCoolingRack2Full) {
		gCoolRack->setTexture("Images\\rack_2.png", this->blockWidth, this->blockHeight, false);
	}
	else if (m_bCoolingRack3Full) {
		gCoolRack->setTexture("Images\\rack_3.png", this->blockWidth, this->blockHeight, false);
	}
	else {
		gCoolRack->setTexture("Images\\rack.png", this->blockWidth, this->blockHeight, false);
	}
}

void BakeryScene::UpdateText() {

	if (!m_vsTaskNames.empty()) {

		// this will preview the next action instead of playing the current one
		this->m_textBox->setString(std::string("action: " + this->m_vsTaskNames.front()));
		this->m_textBox->setPosition(blockWidth * 0.05, blockHeight * 0.98); // set to top-middle right

		// create the list of next steps after this task
		int max_steps_to_show = 39 + 1;
		int size = m_vsTaskNames.size() - 1 >= max_steps_to_show ? max_steps_to_show : m_vsTaskNames.size() - 1;
		std::string nextSteps = "Goal: Keep Displays and Cooling Racks\n           Filled with Muffins\n\nNext Steps:";
		for (int i = 1; i < size; i++) 
		{
			nextSteps += "\n" + std::to_string(i + 1) + ". " + m_vsTaskNames.at(i);
		}

		this->m_nextStepsTextBox->setString(nextSteps);
	}
}

void BakeryScene::UpdateTasks() {


	if(!this->m_vaRecipe.empty())
	{
		std::string temp = this->m_vaRecipe.front().getName();

		if (temp == m_c_bake_muffins) { BakeMuffins(); }
		else if (temp == m_c_clean_mixer){ CleanMixer(); }
		else if (temp == m_c_clean_muffin_tray){ CleanMuffinTray(); }
		else if (temp == m_c_close_fridge){ CloseFridge(); }
		else if (temp == m_c_close_oven){ CloseOven(); }
		else if (temp == m_c_close_pantry){ ClosePantry(); }
		else if (temp == m_c_get_cold_ingredients){ GetColdIngredients(); }
		else if (temp == m_c_get_pantry_ingredients){ GetPantryIngredients(); }
		else if (temp == m_c_mix_ingredients){ MixIngredients(); }
		else if (temp == m_c_move_to_cooling_rack){ MoveToCoolingRack(); }
		else if (temp == m_c_move_to_display_case_1){ MoveToDisplayCase1(); }
		else if (temp == m_c_move_to_display_case_2){ MoveToDisplayCase2(); }
		else if (temp == m_c_move_to_display_case_3){ MoveToDisplayCase3(); }
		else if (temp == m_c_move_to_fridge){ MoveToFridge(); }
		else if (temp == m_c_move_to_mixer){ MoveToMixer(); }
		else if (temp == m_c_move_to_oven){ MoveToOven(); }
		else if (temp == m_c_move_to_pantry){ MoveToPantry(); }
		else if (temp == m_c_move_to_sink){ MoveToSink(); }
		else if (temp == m_c_open_fridge){ OpenFridge(); }
		else if (temp == m_c_open_oven){ OpenOven(); }
		else if (temp == m_c_open_pantry){ OpenPantry(); }
		else if (temp == m_c_place_muffins_in_display_case_1){ PlaceMuffinsInDisplayCase1(); MoveToDisplayCase1();}
		else if (temp == m_c_place_muffins_in_display_case_2){ PlaceMuffinsInDisplayCase2(); MoveToDisplayCase2();}
		else if (temp == m_c_place_muffins_in_display_case_3){ PlaceMuffinsInDisplayCase3(); MoveToDisplayCase3();}
		else if (temp == m_c_place_muffins_on_cooling_rack_1){ PlaceMuffinsOnCoolingRack1(); MoveToCoolingRack();}
		else if (temp == m_c_place_muffins_on_cooling_rack_2){ PlaceMuffinsOnCoolingRack2(); MoveToCoolingRack();}
		else if (temp == m_c_place_muffins_on_cooling_rack_3){ PlaceMuffinsOnCoolingRack3(); MoveToCoolingRack();}
		else if (temp == m_c_pour_batter_into_tray){ PourBatterIntoTray(); }
		else if (temp == m_c_put_muffin_tray_into_oven){ PutMuffinTrayIntoOven(); }
		else if (temp == m_c_remove_muffin_tray_from_oven){ RemoveMuffinTrayFromOven(); }
		else if (temp == m_c_remove_muffins_from_cooling_rack_1){ RemoveMuffinsFromCoolingRack1(); MoveToCoolingRack(); }
		else if (temp == m_c_remove_muffins_from_cooling_rack_2){ RemoveMuffinsFromCoolingRack2(); MoveToCoolingRack(); }
		else if (temp == m_c_remove_muffins_from_cooling_rack_3){ RemoveMuffinsFromCoolingRack3(); MoveToCoolingRack(); }
		else if (temp == m_c_turn_oven_off){ TurnOvenOff(); }
		else if (temp == m_c_turn_oven_on){ TurnOvenOn(); }
		else if (temp == m_c_turn_sink_off){ TurnSinkOff(); }
		else if (temp == m_c_turn_sink_on){ TurnSinkOn(); }

		this->m_vaRecipe.erase(this->m_vaRecipe.begin());
		this->m_vsTaskNames.erase(this->m_vsTaskNames.begin());
	}
}
