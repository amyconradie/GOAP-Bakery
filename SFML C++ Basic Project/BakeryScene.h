#ifndef BAKERYSCENE_H
#define BAKERYSCENE_H

#include "Scene.h"
#include "pch.h"

class BakeryScene :
	public Scene
{

private:

	// private variables
	//-------------------

	sf::RenderWindow* m_RenderWindow;
	sf::VideoMode* m_VideoMode;
	sf::Vector2i m_v2iMousePosWindow;
	sf::Vector2f m_v2fMousePosView;
	sf::Vector2u m_v2uOldWindowSize;

	std::vector<GameObject*> m_vGameObjects;
	GameObject* gOven;
	GameObject* gMixer;
	GameObject* gPantry;
	GameObject* gSink;
	GameObject* gFridge;
	GameObject* gCoolRack;
	GameObject* gDisplayCase1;
	GameObject* gDisplayCase2;
	GameObject* gDisplayCase3;
	GameObject* gBaker;

	sf::Font m_font;
	sf::Text* m_textBox;

	const char* m_cTitle;
	bool m_bToggle = true; // for screen toggle

	unsigned int width;
	unsigned int height;
	unsigned int blockWidth;
	unsigned int blockHeight;

	std::vector<Action> m_vaRecipe;
	MuffinRecipe* m_MuffinRecipe;
	State* currentWorldState;
	std::string m_sCurrentTask;
	int muffinCount = 0;

	sf::Vector2f m_iCoolingRackPos;
	sf::Vector2f m_iMixerPos;
	sf::Vector2f m_iOvenPos;
	sf::Vector2f m_iFridgePos;
	sf::Vector2f m_iPantryPos;
	sf::Vector2f m_iSinkPos;
	sf::Vector2f m_iCoolingrackPos;
	sf::Vector2f m_iDisplayCase1Pos;
	sf::Vector2f m_iDisplayCase2Pos;
	sf::Vector2f m_iDisplayCase3Pos;


	// names of smaller tasks

	const char* m_c_bake_muffins = "bake muffins";
	const char* m_c_clean_mixer = "clean mixer";
	const char* m_c_clean_muffin_tray = "clean muffin tray";
	const char* m_c_close_fridge = "close fridge";
	const char* m_c_close_oven = "close oven";
	const char* m_c_close_pantry = "close pantry";
	const char* m_c_get_cold_ingredients = "get cold ingredients";
	const char* m_c_get_pantry_ingredients = "get pantry ingredients";
	const char* m_c_mix_ingredients = "mix ingredients";
	const char* m_c_move_to_cooling_rack = "move to cooling rack";
	const char* m_c_move_to_display_case_1 = "move to display case 1";
	const char* m_c_move_to_display_case_2 = "move to display case 2";
	const char* m_c_move_to_display_case_3 = "move to display case 3";
	const char* m_c_move_to_fridge = "move to fridge";
	const char* m_c_move_to_mixer = "move to mixer";
	const char* m_c_move_to_oven = "move to oven";
	const char* m_c_move_to_pantry = "move to pantry";
	const char* m_c_move_to_sink = "move to sink";
	const char* m_c_open_fridge = "open fridge";
	const char* m_c_open_oven = "open oven";
	const char* m_c_open_pantry = "open pantry";
	const char* m_c_place_muffins_in_display_case_1 = "place muffins in display case 1";
	const char* m_c_place_muffins_in_display_case_2 = "place muffins in display case 2";
	const char* m_c_place_muffins_in_display_case_3 = "place muffins in display case 3";
	const char* m_c_place_muffins_on_cooling_rack_1 = "place muffins on cooling rack 1";
	const char* m_c_place_muffins_on_cooling_rack_2 = "place muffins on cooling rack 2";
	const char* m_c_place_muffins_on_cooling_rack_3 = "place muffins on cooling rack 3";
	const char* m_c_pour_batter_into_tray = "pour batter into tray";
	const char* m_c_put_muffin_tray_into_oven = "put muffin tray into oven";
	const char* m_c_remove_muffin_tray_from_oven = "remove muffin tray from oven";
	const char* m_c_remove_muffins_from_cooling_rack_1 = "remove muffins from cooling rack 1";
	const char* m_c_remove_muffins_from_cooling_rack_2 = "remove muffins from cooling rack 2";
	const char* m_c_remove_muffins_from_cooling_rack_3 = "remove muffins from cooling rack 3";
	const char* m_c_turn_oven_off = "turn oven off";
	const char* m_c_turn_oven_on = "turn oven on";
	const char* m_c_turn_sink_off = "turn sink off";
	const char* m_c_turn_sink_on = "turn sink on";

public:

	// constructors & destructors
	//----------------------------

	BakeryScene();
	~BakeryScene();


	// important functions
	//---------------------

	virtual void init(sf::RenderWindow* _RenderWindow, sf::VideoMode* _videoMode);
	virtual void update(float _fDeltaTime, sf::Event* event);
	virtual void render();


	// other functions
	//-----------------

	sf::View calcView(sf::Vector2u _v2uWindowSize, sf::Vector2f _v2fDesignedSize);
	void MaintainAspectRatio(bool _bRescaleWindow);
	void toggleFullscreen();
	virtual const char* getTitle();
	virtual void setTitle(const char* _cTitle);
	virtual void updateMousePositions(float _fDeltaTime);

	//State PerformActionsOnState(std::vector<Action> _actions, State _initialState);

	GameObject* CreateGameObject(sf::Color _color, unsigned int _width, unsigned int _height, unsigned int _xpos, unsigned int _ypos);
	GameObject* CreateGameObject(const char* _cFileName, bool _bRepeat, unsigned int _width, unsigned int _height, unsigned int _xpos, unsigned int _ypos);
	State PerformActionsOnState(std::vector<Action> _actions, State _initialState);

	void OpenPantry();
	void ClosePantry();

	void OpenFridge();
	void CloseFridge();

	void OpenOven();
	void CloseOven();

	void TurnOvenOff();
	void TurnOvenOn();

	void TurnSinkOff();
	void TurnSinkOn();

	void CleanMixer();
	void CleanMuffinTray();

	void GetColdIngredients();
	void GetPantryIngredients();
	void MixIngredients();
	
	void PourBatterIntoTray();
	void PutMuffinTrayIntoOven();
	void BakeMuffins();
	void RemoveMuffinTrayFromOven();
	
	void MoveToCoolingRack();
	
	void MoveToDisplayCase1();
	void MoveToDisplayCase2();
	void MoveToDisplayCase3();
	
	void MoveToFridge();
	void MoveToMixer();
	void MoveToOven();
	void MoveToPantry();
	void MoveToSink();
	
	void PlaceMuffinsInDisplayCase1();
	void PlaceMuffinsInDisplayCase2();
	void PlaceMuffinsInDisplayCase3();
	
	void PlaceMuffinsOnCoolingRack1();
	void PlaceMuffinsOnCoolingRack2();
	void PlaceMuffinsOnCoolingRack3();
	
	void RemoveMuffinsFromCoolingRack1();
	void RemoveMuffinsFromCoolingRack2();
	void RemoveMuffinsFromCoolingRack3();

	void UpdateText();
	void UpdateTasks();
};

#endif