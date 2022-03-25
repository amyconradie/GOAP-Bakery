#ifndef MUFFINRECIPE_H
#define MUFFINRECIPE_H

#include "GameObject.h"
#include "Planner.h"

#include "pch.h"

/*
	*Agent Class*
	- extends GameObject and Planner
*/
class MuffinRecipe :
	public GameObject
{

private:

	// private variables
	//-------------------



	// names of larger tasks

	const char* m_cMakeMuffinBatter = "make muffin batter";
	const char* m_cBakeMuffinsInOven = "bake muffins";
	const char* m_cPutMuffinsOnRack1 = "add muffins to cooling rack 1";
	const char* m_cPutMuffinsOnRack2 = "add muffins to cooling rack 2";
	const char* m_cPutMuffinsOnRack3 = "add muffins to cooling rack 3";
	const char* m_cPutWarmMuffinsInDisplay1 = "add muffins to display case 1 from oven";
	const char* m_cPutWarmMuffinsInDisplay2 = "add muffins to display case 2 from oven";
	const char* m_cPutWarmMuffinsInDisplay3 = "add muffins to display case 3 from oven";
	const char* m_cPutColdMuffinsInDisplay1FromRack1 = "add muffins to display case 1 from rack 1";
	const char* m_cPutColdMuffinsInDisplay1FromRack2 = "add muffins to display case 1 from rack 2";
	const char* m_cPutColdMuffinsInDisplay1FromRack3 = "add muffins to display case 1 from rack 3";
	const char* m_cPutColdMuffinsInDisplay2FromRack1 = "add muffins to display case 2 from rack 1";
	const char* m_cPutColdMuffinsInDisplay2FromRack2 = "add muffins to display case 2 from rack 2";
	const char* m_cPutColdMuffinsInDisplay2FromRack3 = "add muffins to display case 2 from rack 3";
	const char* m_cPutColdMuffinsInDisplay3FromRack1 = "add muffins to display case 3 from rack 1";
	const char* m_cPutColdMuffinsInDisplay3FromRack2 = "add muffins to display case 3 from rack 2";
	const char* m_cPutColdMuffinsInDisplay3FromRack3 = "add muffins to display case 3 from rack 3";



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



	// costs

	int cheap = 5;
	int pricey = 15;
	int expensive = 30;


public:


	State currentWorldState;

	// constant variables for states

	const int pantry_open = 1;
	const int fridge_open = 2;
	const int oven_open = 3;

	const int sink_on = 4;
	const int oven_on = 6;
	const int mixer_on = 5;

	const int mixer_clean = 7;
	const int muffin_tray_clean = 8;

	const int have_pantry_ingredients = 9;
	const int have_cold_ingredients = 10;
	const int have_muffin_batter = 11;

	const int muffin_tray_contains_batter = 12;
	const int tray_in_oven = 13;
	const int muffin_tray_contains_muffins = 14;

	const int atPantry = 15;
	const int atFridge = 16;
	const int atMixer = 17;
	const int atOven = 18;
	const int atSink = 19;
	const int atCoolingRack = 20;
	const int atDisplayCase1 = 21;
	const int atDisplayCase2 = 22;
	const int atDisplayCase3 = 23;

	const int cooling_rack_1_is_full = 24;
	const int cooling_rack_2_is_full = 25;
	const int cooling_rack_3_is_full = 26;

	const int display_case_1_is_full = 27;
	const int display_case_2_is_full = 28;
	const int display_case_3_is_full = 29;

	const int hasCooledMuffins = 30;

	// Constructors and Destructors
	//------------------------------

	MuffinRecipe();
	~MuffinRecipe();

	//std::vector<Action> MakeMuffins();
	//int GetTaskCost(std::vector<Action> _actions);
	//State PerformActionsOnState(std::vector<Action> _actions, State _initialState);
	//void updateStateFromWorld(bool _bPantryOpen, bool _bFridgeOpen, bool _bOvenOpen, bool _bSinkOn, bool _bMixerOn, bool _bRack1Full, bool _bRack2Full, bool _bRack3Full, bool _bDisplay1Full, bool _bDisplay2Full, bool _bDisplay3Full);
	//void setCurrentState(State _state);
	//State getCurrentState();
	State GetBeginningState();
	std::vector<Action> BasicPlan(State _initialState);
	std::vector<Action> MakeMuffinBatter(State _initialState);
	std::vector<Action> BakeMuffinsInOven(State _initialState);
	State PerformActionsOnState(std::vector<Action> _actions, State _initialState);
	std::vector<Action> PlaceMuffinsInDisplayCaseFromRackByNum(State _initialState, const int _coolingRackNumFull, int _rackCaseNum, const int _displayCaseNumFull, const int _atDisplayCaseNum, int _displayCaseNum);
	std::vector<Action> PutMuffinsInDisplayCaseByNumFromOven(State _initialState, const int _displayCaseNumFull, const int _atDisplayCaseNum, const int _displayNum);
	std::vector<Action> PutMuffinsInCoolingRackByNum(State _initialState, const int _coolingRackNumFull, int _rackCaseNum);
	std::vector<Action> GetMuffinRecipe();
	int GetTaskCost(std::vector<Action> _actions);
	//std::vector<Action> RemoveMuffinsToDisplayCaseFromRackByNum(State _initialState, const int _coolingRackNumFull, const int _displayCaseNumFull, const int _atDisplayCaseNum);
	////std::vector<Action> RemoveMuffinsToDisplayCaseFromRackByNum(State _initialState, const int _coolingRackNumFull, const int _displayCaseNumFull, const int _atDisplayCaseNum, int _displaycaseNum);
	//std::vector<Action> PutMuffinsInDisplayCaseByNumFromOven(State _initialState, const int _displayCaseNumFull, const int _atDisplayCaseNum);
	//std::vector<Action> PutMuffinsInCoolingRackByNum(State _initialState, const int _coolingRackNumFull);
};

#endif