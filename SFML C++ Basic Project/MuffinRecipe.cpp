#include "MuffinRecipe.h"
#include <sstream>

MuffinRecipe::MuffinRecipe()
{
	currentWorldState = GetBeginningState();
}

MuffinRecipe::~MuffinRecipe()
{
}

State MuffinRecipe::GetBeginningState()
{
	State initial_state;

	initial_state.setVariableById(pantry_open, false);
	initial_state.setVariableById(fridge_open, false);
	initial_state.setVariableById(oven_open, false);

	initial_state.setVariableById(sink_on, false);
	initial_state.setVariableById(oven_on, false);
	initial_state.setVariableById(mixer_on, false);

	initial_state.setVariableById(mixer_clean, true);
	initial_state.setVariableById(muffin_tray_clean, true);

	initial_state.setVariableById(have_pantry_ingredients, false);
	initial_state.setVariableById(have_cold_ingredients, false);
	initial_state.setVariableById(have_muffin_batter, false);

	initial_state.setVariableById(muffin_tray_contains_batter, false);
	initial_state.setVariableById(tray_in_oven, false);
	initial_state.setVariableById(muffin_tray_contains_muffins, false);

	initial_state.setVariableById(atPantry, false);
	initial_state.setVariableById(atFridge, false);
	initial_state.setVariableById(atMixer, false);
	initial_state.setVariableById(atOven, false);
	initial_state.setVariableById(atSink, false);
	initial_state.setVariableById(atCoolingRack, false);
	initial_state.setVariableById(atDisplayCase1, false);
	initial_state.setVariableById(atDisplayCase2, false);
	initial_state.setVariableById(atDisplayCase3, false);

	initial_state.setVariableById(cooling_rack_1_is_full, false);
	initial_state.setVariableById(cooling_rack_2_is_full, false);
	initial_state.setVariableById(cooling_rack_3_is_full, false);

	initial_state.setVariableById(display_case_1_is_full, false);
	initial_state.setVariableById(display_case_2_is_full, false);
	initial_state.setVariableById(display_case_3_is_full, false);

	initial_state.setVariableById(hasCooledMuffins, false);

	return initial_state;
}

std::vector<Action> MuffinRecipe::BasicPlan(State _initialState)
{
	std::vector<Action> simpleActions;
	const char* cTaskName = "Task: Filling Display Cases";

	Action a_makeMuffinBatter(m_cMakeMuffinBatter, expensive);
	a_makeMuffinBatter.setPrecondition(have_muffin_batter, false);
	a_makeMuffinBatter.setEffect(have_muffin_batter, true);
	simpleActions.push_back(a_makeMuffinBatter);

	Action a_bakeMuffins(m_cBakeMuffinsInOven, expensive);
	a_bakeMuffins.setPrecondition(have_muffin_batter, true);
	a_bakeMuffins.setPrecondition(muffin_tray_contains_muffins, false);
	a_bakeMuffins.setEffect(have_muffin_batter, false);
	a_bakeMuffins.setEffect(muffin_tray_contains_muffins, true);
	simpleActions.push_back(a_bakeMuffins);

	Action a_putMuffinsOnCoolingRack1(m_cPutMuffinsOnRack1, cheap);
	a_putMuffinsOnCoolingRack1.setPrecondition(muffin_tray_contains_muffins, true);
	a_putMuffinsOnCoolingRack1.setPrecondition(cooling_rack_1_is_full, false);
	a_putMuffinsOnCoolingRack1.setEffect(muffin_tray_contains_muffins, false);
	a_putMuffinsOnCoolingRack1.setEffect(cooling_rack_1_is_full, true);
	simpleActions.push_back(a_putMuffinsOnCoolingRack1);

	Action a_putMuffinsOnCoolingRack2(m_cPutMuffinsOnRack2, cheap);
	a_putMuffinsOnCoolingRack2.setPrecondition(muffin_tray_contains_muffins, true);
	a_putMuffinsOnCoolingRack2.setPrecondition(cooling_rack_2_is_full, false);
	a_putMuffinsOnCoolingRack2.setEffect(muffin_tray_contains_muffins, false);
	a_putMuffinsOnCoolingRack2.setEffect(cooling_rack_2_is_full, true);
	simpleActions.push_back(a_putMuffinsOnCoolingRack2);

	Action a_putMuffinsOnCoolingRack3(m_cPutMuffinsOnRack3, cheap);
	a_putMuffinsOnCoolingRack3.setPrecondition(muffin_tray_contains_muffins, true);
	a_putMuffinsOnCoolingRack3.setPrecondition(cooling_rack_3_is_full, false);
	a_putMuffinsOnCoolingRack3.setEffect(muffin_tray_contains_muffins, false);
	a_putMuffinsOnCoolingRack3.setEffect(cooling_rack_3_is_full, true);
	simpleActions.push_back(a_putMuffinsOnCoolingRack3);


	//// worked before, is causing problems now?

	//Action a_putMuffinsInDisplayCase1FromOven(m_cPutWarmMuffinsInDisplay1, pricey);
	//a_putMuffinsInDisplayCase1FromOven.setPrecondition(muffin_tray_contains_muffins, true);
	//a_putMuffinsInDisplayCase1FromOven.setPrecondition(display_case_1_is_full, false);
	//a_putMuffinsInDisplayCase1FromOven.setEffect(muffin_tray_contains_muffins, false);
	//a_putMuffinsInDisplayCase1FromOven.setEffect(display_case_1_is_full, true);
	//simpleActions.push_back(a_putMuffinsInDisplayCase1FromOven);
	//
	//Action a_putMuffinsInDisplayCase2FromOven(m_cPutWarmMuffinsInDisplay2, pricey);
	//a_putMuffinsInDisplayCase2FromOven.setPrecondition(muffin_tray_contains_muffins, true);
	//a_putMuffinsInDisplayCase2FromOven.setPrecondition(display_case_2_is_full, false);
	//a_putMuffinsInDisplayCase2FromOven.setEffect(muffin_tray_contains_muffins, false);
	//a_putMuffinsInDisplayCase2FromOven.setEffect(display_case_2_is_full, true);
	//simpleActions.push_back(a_putMuffinsInDisplayCase2FromOven);
	//
	//Action a_putMuffinsInDisplayCase3FromOven(m_cPutWarmMuffinsInDisplay3, pricey);
	//a_putMuffinsInDisplayCase3FromOven.setPrecondition(muffin_tray_contains_muffins, true);
	//a_putMuffinsInDisplayCase3FromOven.setPrecondition(display_case_3_is_full, false);
	//a_putMuffinsInDisplayCase3FromOven.setEffect(muffin_tray_contains_muffins, false);
	//a_putMuffinsInDisplayCase3FromOven.setEffect(display_case_3_is_full, true);
	//simpleActions.push_back(a_putMuffinsInDisplayCase3FromOven);

	Action a_putMuffinsInDisplayCase1FromRack1(m_cPutColdMuffinsInDisplay1FromRack1, cheap);
	a_putMuffinsInDisplayCase1FromRack1.setPrecondition(cooling_rack_1_is_full, true);
	a_putMuffinsInDisplayCase1FromRack1.setPrecondition(display_case_1_is_full, false);
	a_putMuffinsInDisplayCase1FromRack1.setEffect(cooling_rack_1_is_full, false);
	a_putMuffinsInDisplayCase1FromRack1.setEffect(display_case_1_is_full, true);
	simpleActions.push_back(a_putMuffinsInDisplayCase1FromRack1);

	Action a_putMuffinsInDisplayCase1FromRack2(m_cPutColdMuffinsInDisplay1FromRack2, cheap);
	a_putMuffinsInDisplayCase1FromRack2.setPrecondition(cooling_rack_1_is_full, true);
	a_putMuffinsInDisplayCase1FromRack2.setPrecondition(display_case_1_is_full, false);
	a_putMuffinsInDisplayCase1FromRack2.setEffect(cooling_rack_1_is_full, false);
	a_putMuffinsInDisplayCase1FromRack2.setEffect(display_case_1_is_full, true);
	simpleActions.push_back(a_putMuffinsInDisplayCase1FromRack2);

	Action a_putMuffinsInDisplayCase1FromRack3(m_cPutColdMuffinsInDisplay1FromRack3, cheap);
	a_putMuffinsInDisplayCase1FromRack3.setPrecondition(cooling_rack_3_is_full, true);
	a_putMuffinsInDisplayCase1FromRack3.setPrecondition(display_case_1_is_full, false);
	a_putMuffinsInDisplayCase1FromRack3.setEffect(cooling_rack_3_is_full, false);
	a_putMuffinsInDisplayCase1FromRack3.setEffect(display_case_1_is_full, true);
	simpleActions.push_back(a_putMuffinsInDisplayCase1FromRack3);

	Action a_putMuffinsInDisplayCase2FromRack1(m_cPutColdMuffinsInDisplay2FromRack1, cheap);
	a_putMuffinsInDisplayCase2FromRack1.setPrecondition(cooling_rack_1_is_full, true);
	a_putMuffinsInDisplayCase2FromRack1.setPrecondition(display_case_2_is_full, false);
	a_putMuffinsInDisplayCase2FromRack1.setEffect(cooling_rack_1_is_full, false);
	a_putMuffinsInDisplayCase2FromRack1.setEffect(display_case_2_is_full, true);
	simpleActions.push_back(a_putMuffinsInDisplayCase2FromRack1);
	
	Action a_putMuffinsInDisplayCase2FromRack2(m_cPutColdMuffinsInDisplay2FromRack2, cheap);
	a_putMuffinsInDisplayCase2FromRack2.setPrecondition(cooling_rack_2_is_full, true);
	a_putMuffinsInDisplayCase2FromRack2.setPrecondition(display_case_2_is_full, false);
	a_putMuffinsInDisplayCase2FromRack2.setEffect(cooling_rack_2_is_full, false);
	a_putMuffinsInDisplayCase2FromRack2.setEffect(display_case_2_is_full, true);
	simpleActions.push_back(a_putMuffinsInDisplayCase2FromRack2);
	
	Action a_putMuffinsInDisplayCase2FromRack3(m_cPutColdMuffinsInDisplay2FromRack3, cheap);
	a_putMuffinsInDisplayCase2FromRack3.setPrecondition(cooling_rack_3_is_full, true);
	a_putMuffinsInDisplayCase2FromRack3.setPrecondition(display_case_2_is_full, false);
	a_putMuffinsInDisplayCase2FromRack3.setEffect(cooling_rack_3_is_full, false);
	a_putMuffinsInDisplayCase2FromRack3.setEffect(display_case_2_is_full, true);
	simpleActions.push_back(a_putMuffinsInDisplayCase2FromRack3);
	
	Action a_putMuffinsInDisplayCase3FromRack1(m_cPutColdMuffinsInDisplay3FromRack1, cheap);
	a_putMuffinsInDisplayCase3FromRack1.setPrecondition(cooling_rack_1_is_full, true);
	a_putMuffinsInDisplayCase3FromRack1.setPrecondition(display_case_3_is_full, false);
	a_putMuffinsInDisplayCase3FromRack1.setEffect(cooling_rack_1_is_full, false);
	a_putMuffinsInDisplayCase3FromRack1.setEffect(display_case_3_is_full, true);
	simpleActions.push_back(a_putMuffinsInDisplayCase3FromRack1);
	
	Action a_putMuffinsInDisplayCase3FromRack2(m_cPutColdMuffinsInDisplay3FromRack2, cheap);
	a_putMuffinsInDisplayCase3FromRack2.setPrecondition(cooling_rack_2_is_full, true);
	a_putMuffinsInDisplayCase3FromRack2.setPrecondition(display_case_3_is_full, false);
	a_putMuffinsInDisplayCase3FromRack2.setEffect(cooling_rack_2_is_full, false);
	a_putMuffinsInDisplayCase3FromRack2.setEffect(display_case_3_is_full, true);
	simpleActions.push_back(a_putMuffinsInDisplayCase3FromRack2);
	
	Action a_putMuffinsInDisplayCase3FromRack3(m_cPutColdMuffinsInDisplay3FromRack3, cheap);
	a_putMuffinsInDisplayCase3FromRack3.setPrecondition(cooling_rack_3_is_full, true);
	a_putMuffinsInDisplayCase3FromRack3.setPrecondition(display_case_3_is_full, false);
	a_putMuffinsInDisplayCase3FromRack3.setEffect(cooling_rack_3_is_full, false);
	a_putMuffinsInDisplayCase3FromRack3.setEffect(display_case_3_is_full, true);
	simpleActions.push_back(a_putMuffinsInDisplayCase3FromRack3);

	// Desired State
	State goalState;
	goalState.setVariableById(display_case_1_is_full, true);
	goalState.setVariableById(display_case_2_is_full, true);
	goalState.setVariableById(display_case_3_is_full, true);
	goalState.setVariableById(cooling_rack_1_is_full, true);
	goalState.setVariableById(cooling_rack_2_is_full, true);
	goalState.setVariableById(cooling_rack_3_is_full, true);
	goalState.m_fPriorityLevel = 100;

	// A*
	Planner aStarPlanner;
	try {
		std::vector<Action> the_plan = aStarPlanner.plan(_initialState, goalState, simpleActions);

		std::vector<Action> steps; // reversed order

		// reverse the order
		for (std::vector<Action>::reverse_iterator rit = the_plan.rbegin(); rit != the_plan.rend(); ++rit) {
			auto idx = std::distance(begin(the_plan), rit.base()) - 1;
			steps.push_back(the_plan.at(idx));
		}

		int i = 1;
		for (auto& step : steps) {
			std::cout << "step " << i++ << ": " << step.getName() << "\n";
		}

		return steps;
	}
	catch (const std::exception&) {
		std::cout << "no path found for " << cTaskName << "\n";
	}

	return std::vector<Action>();
}

std::vector<Action> MuffinRecipe::MakeMuffinBatter(State _initialState)
{
	// list of actions that could possibly occur in plan
	std::vector<Action> actions;
	const char* cTaskName = "Task: Making Muffin Batter";

	// move actions

	Action a_moveToPantry = Action("move to pantry", pricey);
	a_moveToPantry.setPrecondition(atPantry, false);
	a_moveToPantry.setEffect(atPantry, true);
	a_moveToPantry.setEffect(atFridge, false);
	a_moveToPantry.setEffect(atMixer, false);
	a_moveToPantry.setEffect(atOven, false);
	a_moveToPantry.setEffect(atSink, false);
	a_moveToPantry.setEffect(atCoolingRack, false);
	a_moveToPantry.setEffect(atDisplayCase1, false);
	a_moveToPantry.setEffect(atDisplayCase2, false);
	a_moveToPantry.setEffect(atDisplayCase3, false);
	actions.push_back(a_moveToPantry);

	Action a_moveToFridge = Action("move to fridge", pricey);
	a_moveToFridge.setPrecondition(atFridge, false);
	a_moveToFridge.setEffect(atPantry, false);
	a_moveToFridge.setEffect(atFridge, true);
	a_moveToFridge.setEffect(atMixer, false);
	a_moveToFridge.setEffect(atOven, false);
	a_moveToFridge.setEffect(atSink, false);
	a_moveToFridge.setEffect(atCoolingRack, false);
	a_moveToFridge.setEffect(atDisplayCase1, false);
	a_moveToFridge.setEffect(atDisplayCase2, false);
	a_moveToFridge.setEffect(atDisplayCase3, false);
	actions.push_back(a_moveToFridge);

	Action a_moveToMixer = Action("move to mixer", pricey);
	a_moveToMixer.setPrecondition(atMixer, false);
	a_moveToMixer.setEffect(atPantry, false);
	a_moveToMixer.setEffect(atFridge, false);
	a_moveToMixer.setEffect(atMixer, true);
	a_moveToMixer.setEffect(atOven, false);
	a_moveToMixer.setEffect(atSink, false);
	a_moveToMixer.setEffect(atCoolingRack, false);
	a_moveToMixer.setEffect(atDisplayCase1, false);
	a_moveToMixer.setEffect(atDisplayCase2, false);
	a_moveToMixer.setEffect(atDisplayCase3, false);
	actions.push_back(a_moveToMixer);

	Action a_moveToSink = Action("move to sink", pricey);
	a_moveToSink.setPrecondition(atSink, false);
	a_moveToSink.setEffect(atPantry, false);
	a_moveToSink.setEffect(atFridge, false);
	a_moveToSink.setEffect(atMixer, false);
	a_moveToSink.setEffect(atOven, false);
	a_moveToSink.setEffect(atSink, true);
	a_moveToSink.setEffect(atCoolingRack, false);
	a_moveToSink.setEffect(atDisplayCase1, false);
	a_moveToSink.setEffect(atDisplayCase2, false);
	a_moveToSink.setEffect(atDisplayCase3, false);
	actions.push_back(a_moveToSink);

	// open/close actions

	Action a_openPantry = Action("open pantry", cheap);
	a_openPantry.setPrecondition(atPantry, true);
	a_openPantry.setPrecondition(pantry_open, false);
	a_openPantry.setEffect(pantry_open, true);
	actions.push_back(a_openPantry);

	Action a_closePantry = Action("close pantry", cheap);
	a_closePantry.setPrecondition(atPantry, true);
	a_closePantry.setPrecondition(pantry_open, true);
	a_closePantry.setEffect(pantry_open, false);
	actions.push_back(a_closePantry);

	Action a_openFridge = Action("open fridge", cheap);
	a_openFridge.setPrecondition(atFridge, true);
	a_openFridge.setPrecondition(fridge_open, false);
	a_openFridge.setEffect(fridge_open, true);
	actions.push_back(a_openFridge);

	Action a_closeFridge = Action("close fridge", cheap);
	a_closeFridge.setPrecondition(atFridge, true);
	a_closeFridge.setPrecondition(fridge_open, true);
	a_closeFridge.setEffect(fridge_open, false);
	actions.push_back(a_closeFridge);


	// on/off actions

	Action a_turnSinkOn = Action("turn sink on", cheap);
	a_turnSinkOn.setPrecondition(atSink, true);
	a_turnSinkOn.setPrecondition(sink_on, false);
	a_turnSinkOn.setEffect(sink_on, true);
	actions.push_back(a_turnSinkOn);

	Action a_turnSinkOff = Action("turn sink off", cheap);
	a_turnSinkOff.setPrecondition(atSink, true);
	a_turnSinkOff.setPrecondition(sink_on, true);
	a_turnSinkOff.setEffect(sink_on, false);
	actions.push_back(a_turnSinkOff);


	// clean actions

	Action a_cleanMixer = Action("clean mixer", pricey);
	a_cleanMixer.setPrecondition(mixer_clean, false);
	a_cleanMixer.setPrecondition(atSink, true);
	a_cleanMixer.setPrecondition(sink_on, true);
	a_cleanMixer.setEffect(mixer_clean, true);
	actions.push_back(a_cleanMixer);


	// get ingredients actions

	Action a_getColdIngredients = Action("get cold ingredients", pricey);
	a_getColdIngredients.setPrecondition(fridge_open, true);
	a_getColdIngredients.setPrecondition(atFridge, true);
	a_getColdIngredients.setPrecondition(have_cold_ingredients, false);
	a_getColdIngredients.setEffect(have_cold_ingredients, true);
	actions.push_back(a_getColdIngredients);

	Action a_getPantryIngredients = Action("get pantry ingredients", pricey);
	a_getPantryIngredients.setPrecondition(pantry_open, true);
	a_getPantryIngredients.setPrecondition(atPantry, true);
	a_getPantryIngredients.setPrecondition(have_pantry_ingredients, false);
	a_getPantryIngredients.setEffect(have_pantry_ingredients, true);
	actions.push_back(a_getPantryIngredients);


	// mixing actions

	Action a_mixIngredients = Action("mix ingredients", expensive);
	a_mixIngredients.setPrecondition(mixer_clean, true);
	a_mixIngredients.setPrecondition(atMixer, true);
	a_mixIngredients.setPrecondition(have_pantry_ingredients, true);
	a_mixIngredients.setPrecondition(have_cold_ingredients, true);
	a_mixIngredients.setEffect(have_muffin_batter, true);
	a_mixIngredients.setEffect(have_pantry_ingredients, false);
	a_mixIngredients.setEffect(have_cold_ingredients, false);
	a_mixIngredients.setEffect(mixer_clean, false);
	actions.push_back(a_mixIngredients);

	// variables required to meet goal

	State s_goalState;
	s_goalState.setVariableById(have_muffin_batter, true);
	s_goalState.setVariableById(muffin_tray_contains_batter, false);
	s_goalState.setVariableById(muffin_tray_contains_muffins, false);
	s_goalState.setVariableById(hasCooledMuffins, false);
	s_goalState.setVariableById(pantry_open, false);
	s_goalState.setVariableById(fridge_open, false);
	s_goalState.setVariableById(sink_on, false);
	s_goalState.m_fPriorityLevel = 100;

	Planner aStarPlanner;
	try
	{
		std::vector<Action> the_plan = aStarPlanner.plan(_initialState, s_goalState, actions);
		std::vector<Action> steps;

		for (std::vector<Action>::reverse_iterator rit = the_plan.rbegin(); rit != the_plan.rend(); ++rit) {
			auto idx = std::distance(begin(the_plan), rit.base()) - 1;
			steps.push_back(the_plan.at(idx));
		}

		return steps;

	}
	catch (const std::exception&) {
		std::cout << "no path found for " << cTaskName << "\n";
	}

	return std::vector<Action>();
}

std::vector<Action> MuffinRecipe::BakeMuffinsInOven(State _initialState)
{
	// list of actions that could possibly occur in plan
	std::vector<Action> actions;
	const char* cTaskName = "Task: Baking Muffins in Oven";


	// move actions

	Action a_moveToOven = Action("move to oven", pricey);
	a_moveToOven.setPrecondition(atOven, false);
	a_moveToOven.setEffect(atPantry, false);
	a_moveToOven.setEffect(atFridge, false);
	a_moveToOven.setEffect(atMixer, false);
	a_moveToOven.setEffect(atOven, true);
	a_moveToOven.setEffect(atSink, false);
	a_moveToOven.setEffect(atCoolingRack, false);
	a_moveToOven.setEffect(atDisplayCase1, false);
	a_moveToOven.setEffect(atDisplayCase2, false);
	a_moveToOven.setEffect(atDisplayCase3, false);
	actions.push_back(a_moveToOven);

	Action a_moveToSink = Action("move to sink", pricey);
	a_moveToSink.setPrecondition(atSink, false);
	a_moveToSink.setEffect(atPantry, false);
	a_moveToSink.setEffect(atFridge, false);
	a_moveToSink.setEffect(atMixer, false);
	a_moveToSink.setEffect(atOven, false);
	a_moveToSink.setEffect(atSink, true);
	a_moveToSink.setEffect(atCoolingRack, false);
	a_moveToSink.setEffect(atDisplayCase1, false);
	a_moveToSink.setEffect(atDisplayCase2, false);
	a_moveToSink.setEffect(atDisplayCase3, false);
	actions.push_back(a_moveToSink);


	// open/close actions

	Action a_openOven = Action("open oven", cheap);
	a_openOven.setPrecondition(atOven, true);
	a_openOven.setPrecondition(oven_open, false);
	a_openOven.setEffect(oven_open, true);
	actions.push_back(a_openOven);

	Action a_closeOven = Action("close oven", cheap);
	a_closeOven.setPrecondition(atOven, true);
	a_closeOven.setPrecondition(oven_open, true);
	a_closeOven.setEffect(oven_open, false);
	actions.push_back(a_closeOven);


	// on/off actions

	Action a_turnSinkOn = Action("turn sink on", cheap);
	a_turnSinkOn.setPrecondition(atSink, true);
	a_turnSinkOn.setPrecondition(sink_on, false);
	a_turnSinkOn.setEffect(sink_on, true);
	actions.push_back(a_turnSinkOn);

	Action a_turnSinkOff = Action("turn sink off", cheap);
	a_turnSinkOff.setPrecondition(atSink, true);
	a_turnSinkOff.setPrecondition(sink_on, true);
	a_turnSinkOff.setEffect(sink_on, false);
	actions.push_back(a_turnSinkOff);

	Action a_turnOvenOn = Action("turn oven on", cheap);
	a_turnOvenOn.setPrecondition(atOven, true);
	a_turnOvenOn.setPrecondition(oven_on, false);
	a_turnOvenOn.setEffect(oven_on, true);
	actions.push_back(a_turnOvenOn);

	Action a_turnOvenOff = Action("turn oven off", cheap);
	a_turnOvenOff.setPrecondition(atOven, true);
	a_turnOvenOff.setPrecondition(oven_on, true);
	a_turnOvenOff.setEffect(oven_on, false);
	actions.push_back(a_turnOvenOff);
	

	// mixing actions

	Action a_pourIntoMuffinTray = Action("pour batter into tray", pricey);
	a_pourIntoMuffinTray.setPrecondition(muffin_tray_clean, true);
	a_pourIntoMuffinTray.setPrecondition(have_muffin_batter, true);
	a_pourIntoMuffinTray.setPrecondition(muffin_tray_contains_batter, false);
	a_pourIntoMuffinTray.setPrecondition(muffin_tray_contains_muffins, false);
	a_pourIntoMuffinTray.setEffect(have_muffin_batter, false);
	a_pourIntoMuffinTray.setEffect(muffin_tray_clean, false);
	a_pourIntoMuffinTray.setEffect(muffin_tray_contains_batter, true);
	actions.push_back(a_pourIntoMuffinTray);


	// baking actions

	Action a_putMuffinTrayInOven = Action("put muffin tray into oven", pricey);
	a_putMuffinTrayInOven.setPrecondition(atOven, true);
	a_putMuffinTrayInOven.setPrecondition(oven_open, true);
	a_putMuffinTrayInOven.setPrecondition(muffin_tray_contains_batter, true);
	a_putMuffinTrayInOven.setPrecondition(tray_in_oven, false);
	a_putMuffinTrayInOven.setEffect(tray_in_oven, true);
	actions.push_back(a_putMuffinTrayInOven);

	Action a_bakeMuffins = Action("bake muffins", expensive);
	a_bakeMuffins.setPrecondition(atOven, true);
	a_bakeMuffins.setPrecondition(tray_in_oven, true);
	a_bakeMuffins.setPrecondition(oven_on, true);
	a_bakeMuffins.setPrecondition(oven_open, false);
	a_bakeMuffins.setPrecondition(muffin_tray_contains_batter, true);
	a_bakeMuffins.setEffect(muffin_tray_contains_batter, false);
	a_bakeMuffins.setEffect(muffin_tray_contains_muffins, true);
	actions.push_back(a_bakeMuffins);

	// goal actions

	Action a_removeMuffinTrayFromOven = Action("remove muffin tray from oven", pricey);
	a_removeMuffinTrayFromOven.setPrecondition(atOven, true);
	a_removeMuffinTrayFromOven.setPrecondition(oven_open, true);
	a_removeMuffinTrayFromOven.setPrecondition(muffin_tray_contains_muffins, true);
	a_removeMuffinTrayFromOven.setPrecondition(tray_in_oven, true);
	a_removeMuffinTrayFromOven.setEffect(tray_in_oven, false);
	actions.push_back(a_removeMuffinTrayFromOven);

	// clean actions

	Action a_cleanMuffinTray = Action("clean muffin tray", pricey);
	a_cleanMuffinTray.setPrecondition(atSink, true);
	a_cleanMuffinTray.setPrecondition(sink_on, true);
	a_cleanMuffinTray.setPrecondition(tray_in_oven, false);
	a_cleanMuffinTray.setPrecondition(muffin_tray_contains_muffins, false);
	a_cleanMuffinTray.setPrecondition(muffin_tray_contains_batter, false);
	a_cleanMuffinTray.setPrecondition(muffin_tray_clean, false);
	a_cleanMuffinTray.setEffect(muffin_tray_clean, true);
	actions.push_back(a_cleanMuffinTray);


	// variables required to meet goal

	State s_goalState;
	s_goalState.setVariableById(muffin_tray_contains_muffins, true);
	s_goalState.setVariableById(tray_in_oven, false);
	s_goalState.setVariableById(have_muffin_batter, false);
	s_goalState.setVariableById(muffin_tray_contains_batter, false);
	s_goalState.setVariableById(sink_on, false);
	s_goalState.setVariableById(oven_on, false);
	s_goalState.setVariableById(oven_open, false);
	s_goalState.m_fPriorityLevel = 100;

	Planner aStarPlanner;
	try
	{
		std::vector<Action> the_plan = aStarPlanner.plan(_initialState, s_goalState, actions);
		std::vector<Action> steps;

		for (std::vector<Action>::reverse_iterator rit = the_plan.rbegin(); rit != the_plan.rend(); ++rit) {
			auto idx = std::distance(begin(the_plan), rit.base()) - 1;
			steps.push_back(the_plan.at(idx));
		}

		if (steps.empty()) {
			std::cout << "no path found for " << cTaskName << "\n";
		}
		return steps;

	}
	catch (const std::exception&) {
		std::cout << "no path found for " << cTaskName << "\n";
	}

	return std::vector<Action>();
}


State MuffinRecipe::PerformActionsOnState(std::vector<Action> _actions, State _initialState)
{
	State tempState = _initialState;

	for (auto& action : _actions) {
		tempState = action.performOnState(tempState);
	}

	return tempState;
}


std::vector<Action> MuffinRecipe::PlaceMuffinsInDisplayCaseFromRackByNum(State _initialState, const int _coolingRackNumFull, int _rackCaseNum, const int _displayCaseNumFull, const int _atDisplayCaseNum, int _displayCaseNum)
{

	// list of actions that could possibly occur in plan

	std::vector<Action> actions;
	const char* cTaskName = "Task: Placing Muffins into Display Case by taking from Cooling Rack";

	Action a_moveToCoolingRack = Action("move to cooling rack", pricey);
	a_moveToCoolingRack.setPrecondition(atCoolingRack, false);
	a_moveToCoolingRack.setEffect(atPantry, false);
	a_moveToCoolingRack.setEffect(atFridge, false);
	a_moveToCoolingRack.setEffect(atMixer, false);
	a_moveToCoolingRack.setEffect(atOven, false);
	a_moveToCoolingRack.setEffect(atSink, false);
	a_moveToCoolingRack.setEffect(atCoolingRack, true);
	a_moveToCoolingRack.setEffect(atDisplayCase1, false);
	a_moveToCoolingRack.setEffect(atDisplayCase2, false);
	a_moveToCoolingRack.setEffect(atDisplayCase3, false);
	actions.push_back(a_moveToCoolingRack);

	if (_displayCaseNum == 1) {

		Action a_moveToDisplayCase1 = Action("move to display case 1", pricey);
		a_moveToDisplayCase1.setPrecondition(atDisplayCase1, false);
		a_moveToDisplayCase1.setEffect(atPantry, false);
		a_moveToDisplayCase1.setEffect(atFridge, false);
		a_moveToDisplayCase1.setEffect(atMixer, false);
		a_moveToDisplayCase1.setEffect(atOven, false);
		a_moveToDisplayCase1.setEffect(atSink, false);
		a_moveToDisplayCase1.setEffect(atCoolingRack, false);
		a_moveToDisplayCase1.setEffect(atDisplayCase1, true);
		a_moveToDisplayCase1.setEffect(atDisplayCase2, false);
		a_moveToDisplayCase1.setEffect(atDisplayCase3, false);
		actions.push_back(a_moveToDisplayCase1);

		Action a_placeMuffinsInDisplayCase1 = Action("place muffins in display case 1", pricey);
		a_placeMuffinsInDisplayCase1.setPrecondition(atDisplayCase1, true);
		a_placeMuffinsInDisplayCase1.setPrecondition(display_case_1_is_full, false);
		a_placeMuffinsInDisplayCase1.setPrecondition(hasCooledMuffins, true);
		a_placeMuffinsInDisplayCase1.setEffect(hasCooledMuffins, false);
		a_placeMuffinsInDisplayCase1.setEffect(display_case_1_is_full, true);
		actions.push_back(a_placeMuffinsInDisplayCase1);
	}
	else if (_displayCaseNum == 2) {

		Action a_moveToDisplayCase2 = Action("move to display case 2", pricey);
		a_moveToDisplayCase2.setPrecondition(atDisplayCase2, false);
		a_moveToDisplayCase2.setEffect(atPantry, false);
		a_moveToDisplayCase2.setEffect(atFridge, false);
		a_moveToDisplayCase2.setEffect(atMixer, false);
		a_moveToDisplayCase2.setEffect(atOven, false);
		a_moveToDisplayCase2.setEffect(atSink, false);
		a_moveToDisplayCase2.setEffect(atCoolingRack, false);
		a_moveToDisplayCase2.setEffect(atDisplayCase1, false);
		a_moveToDisplayCase2.setEffect(atDisplayCase2, true);
		a_moveToDisplayCase2.setEffect(atDisplayCase3, false);
		actions.push_back(a_moveToDisplayCase2);

		Action a_placeMuffinsInDisplayCase2 = Action("place muffins in display case 2", pricey);
		a_placeMuffinsInDisplayCase2.setPrecondition(atDisplayCase2, true);
		a_placeMuffinsInDisplayCase2.setPrecondition(display_case_2_is_full, false);
		a_placeMuffinsInDisplayCase2.setPrecondition(hasCooledMuffins, true);
		a_placeMuffinsInDisplayCase2.setEffect(hasCooledMuffins, false);
		a_placeMuffinsInDisplayCase2.setEffect(display_case_2_is_full, true);
		actions.push_back(a_placeMuffinsInDisplayCase2);
	}
	else if (_displayCaseNum == 3) {

		Action a_moveToDisplayCase3 = Action("move to display case 3", pricey);
		a_moveToDisplayCase3.setPrecondition(atDisplayCase3, false);
		a_moveToDisplayCase3.setEffect(atPantry, false);
		a_moveToDisplayCase3.setEffect(atFridge, false);
		a_moveToDisplayCase3.setEffect(atMixer, false);
		a_moveToDisplayCase3.setEffect(atOven, false);
		a_moveToDisplayCase3.setEffect(atSink, false);
		a_moveToDisplayCase3.setEffect(atCoolingRack, false);
		a_moveToDisplayCase3.setEffect(atDisplayCase1, false);
		a_moveToDisplayCase3.setEffect(atDisplayCase2, false);
		a_moveToDisplayCase3.setEffect(atDisplayCase3, true);
		actions.push_back(a_moveToDisplayCase3);


		Action a_placeMuffinsInDisplayCase3 = Action("place muffins in display case 3", pricey);
		a_placeMuffinsInDisplayCase3.setPrecondition(atDisplayCase3, true);
		a_placeMuffinsInDisplayCase3.setPrecondition(display_case_3_is_full, false);
		a_placeMuffinsInDisplayCase3.setPrecondition(hasCooledMuffins, true);
		a_placeMuffinsInDisplayCase3.setEffect(hasCooledMuffins, false);
		a_placeMuffinsInDisplayCase3.setEffect(display_case_3_is_full, true);
		actions.push_back(a_placeMuffinsInDisplayCase3);
	}

	if (_rackCaseNum == 1) {
		Action a_removeMuffinsFromCoolingRack1 = Action("remove muffins from cooling rack 1", cheap);
		a_removeMuffinsFromCoolingRack1.setPrecondition(atCoolingRack, true);
		a_removeMuffinsFromCoolingRack1.setPrecondition(cooling_rack_1_is_full, true);
		a_removeMuffinsFromCoolingRack1.setEffect(hasCooledMuffins, true);
		a_removeMuffinsFromCoolingRack1.setEffect(cooling_rack_1_is_full, false);
		actions.push_back(a_removeMuffinsFromCoolingRack1);
	}
	else if (_rackCaseNum == 2) {
		Action a_removeMuffinsFromCoolingRack2 = Action("remove muffins from cooling rack 2", cheap);
		a_removeMuffinsFromCoolingRack2.setPrecondition(atCoolingRack, true);
		a_removeMuffinsFromCoolingRack2.setPrecondition(cooling_rack_2_is_full, true);
		a_removeMuffinsFromCoolingRack2.setEffect(hasCooledMuffins, true);
		a_removeMuffinsFromCoolingRack2.setEffect(cooling_rack_2_is_full, false);
		actions.push_back(a_removeMuffinsFromCoolingRack2);
	}
	else if (_rackCaseNum == 3) {
		Action a_removeMuffinsFromCoolingRack3 = Action("remove muffins from cooling rack 3", cheap);
		a_removeMuffinsFromCoolingRack3.setPrecondition(atCoolingRack, true);
		a_removeMuffinsFromCoolingRack3.setPrecondition(cooling_rack_3_is_full, true);
		a_removeMuffinsFromCoolingRack3.setEffect(hasCooledMuffins, true);
		a_removeMuffinsFromCoolingRack3.setEffect(cooling_rack_3_is_full, false);
		actions.push_back(a_removeMuffinsFromCoolingRack3);
	}


	// variables required to meet goal

	State s_goalState;

	if (_displayCaseNum == 1) {
		s_goalState.setVariableById(display_case_1_is_full, true);
		s_goalState.m_fPriorityLevel = 100;

	}
	else if (_displayCaseNum == 2) {
		s_goalState.setVariableById(display_case_2_is_full, true);
		s_goalState.m_fPriorityLevel = 100;

	}
	else if (_displayCaseNum == 3) {
		s_goalState.setVariableById(display_case_3_is_full, true);
		s_goalState.m_fPriorityLevel = 100;

	}

	// A* planner
	Planner aStarPlanner;
	try
	{
		std::vector<Action> the_plan = aStarPlanner.plan(_initialState, s_goalState, actions);
		std::vector<Action> steps;

		for (std::vector<Action>::reverse_iterator rit = the_plan.rbegin(); rit != the_plan.rend(); ++rit) {
			auto idx = std::distance(begin(the_plan), rit.base()) - 1;
			steps.push_back(the_plan.at(idx));
		}

		return steps;

	}
	catch (const std::exception&) {
		std::cout << "no path found for " << cTaskName << "\n";
	}

	return std::vector<Action>();
}

std::vector<Action> MuffinRecipe::PutMuffinsInDisplayCaseByNumFromOven(State _initialState, const int _displayCaseNumFull, const int _atDisplayCaseNum, const int _displayNum)
{

	// list of actions that could possibly occur in plan

	std::vector<Action> actions;
	std::string temp = std::string("Task: Placing Muffins into Display Case" + _displayNum);
	const char* cTaskName = temp.c_str();

	// actions

	if (_displayNum == 1) 
	{
		Action a_moveToDisplayCase1 = Action("move to display case 1", pricey);
		a_moveToDisplayCase1.setPrecondition(atDisplayCase1, false);
		a_moveToDisplayCase1.setEffect(atPantry, false);
		a_moveToDisplayCase1.setEffect(atFridge, false);
		a_moveToDisplayCase1.setEffect(atMixer, false);
		a_moveToDisplayCase1.setEffect(atOven, false);
		a_moveToDisplayCase1.setEffect(atSink, false);
		a_moveToDisplayCase1.setEffect(atCoolingRack, false);
		a_moveToDisplayCase1.setEffect(atDisplayCase1, true);
		a_moveToDisplayCase1.setEffect(atDisplayCase2, false);
		a_moveToDisplayCase1.setEffect(atDisplayCase3, false);
		actions.push_back(a_moveToDisplayCase1);


		Action a_placeMuffinsInDisplayCase1 = Action("place muffins in display case 1", pricey);
		a_placeMuffinsInDisplayCase1.setPrecondition(atDisplayCase1, true);
		a_placeMuffinsInDisplayCase1.setPrecondition(display_case_1_is_full, false);
		a_placeMuffinsInDisplayCase1.setPrecondition(muffin_tray_contains_muffins, true);
		a_placeMuffinsInDisplayCase1.setEffect(muffin_tray_contains_muffins, false);
		a_placeMuffinsInDisplayCase1.setEffect(display_case_1_is_full, true);
		actions.push_back(a_placeMuffinsInDisplayCase1);
	}
	else if (_displayNum == 2) 
	{
		Action a_moveToDisplayCase2 = Action("move to display case 2", pricey);
		a_moveToDisplayCase2.setPrecondition(atDisplayCase2, false);
		a_moveToDisplayCase2.setEffect(atPantry, false);
		a_moveToDisplayCase2.setEffect(atFridge, false);
		a_moveToDisplayCase2.setEffect(atMixer, false);
		a_moveToDisplayCase2.setEffect(atOven, false);
		a_moveToDisplayCase2.setEffect(atSink, false);
		a_moveToDisplayCase2.setEffect(atCoolingRack, false);
		a_moveToDisplayCase2.setEffect(atDisplayCase1, false);
		a_moveToDisplayCase2.setEffect(atDisplayCase2, true);
		a_moveToDisplayCase2.setEffect(atDisplayCase3, false);
		actions.push_back(a_moveToDisplayCase2);


		Action a_placeMuffinsInDisplayCase2 = Action("place muffins in display case 2", pricey);
		a_placeMuffinsInDisplayCase2.setPrecondition(atDisplayCase2, true);
		a_placeMuffinsInDisplayCase2.setPrecondition(display_case_2_is_full, false);
		a_placeMuffinsInDisplayCase2.setPrecondition(muffin_tray_contains_muffins, true);
		a_placeMuffinsInDisplayCase2.setEffect(muffin_tray_contains_muffins, false);
		a_placeMuffinsInDisplayCase2.setEffect(display_case_2_is_full, true);
		actions.push_back(a_placeMuffinsInDisplayCase2);
	}
	else if (_displayNum == 3) 
	{
		Action a_moveToDisplayCase3 = Action("move to display case 3", pricey);
		a_moveToDisplayCase3.setPrecondition(atDisplayCase3, false);
		a_moveToDisplayCase3.setEffect(atPantry, false);
		a_moveToDisplayCase3.setEffect(atFridge, false);
		a_moveToDisplayCase3.setEffect(atMixer, false);
		a_moveToDisplayCase3.setEffect(atOven, false);
		a_moveToDisplayCase3.setEffect(atSink, false);
		a_moveToDisplayCase3.setEffect(atCoolingRack, false);
		a_moveToDisplayCase3.setEffect(atDisplayCase1, false);
		a_moveToDisplayCase3.setEffect(atDisplayCase2, false);
		a_moveToDisplayCase3.setEffect(atDisplayCase3, true);
		actions.push_back(a_moveToDisplayCase3);


		Action a_placeMuffinsInDisplayCase3 = Action("place muffins in display case 3", pricey);
		a_placeMuffinsInDisplayCase3.setPrecondition(atDisplayCase3, true);
		a_placeMuffinsInDisplayCase3.setPrecondition(display_case_3_is_full, false);
		a_placeMuffinsInDisplayCase3.setPrecondition(muffin_tray_contains_muffins, true);
		a_placeMuffinsInDisplayCase3.setEffect(muffin_tray_contains_muffins, false);
		a_placeMuffinsInDisplayCase3.setEffect(display_case_3_is_full, true);
		actions.push_back(a_placeMuffinsInDisplayCase3);
	}



	// variables required to meet goal

	State s_goalState;
	if (_atDisplayCaseNum == 1) 
	{
		s_goalState.setVariableById(display_case_1_is_full, true);
		s_goalState.m_fPriorityLevel = 100;
	}
	else if (_atDisplayCaseNum == 2) 
	{
		s_goalState.setVariableById(display_case_2_is_full, true);
		s_goalState.m_fPriorityLevel = 100;

	}
	else if (_atDisplayCaseNum == 3) 
	{
		s_goalState.setVariableById(display_case_3_is_full, true);
		s_goalState.m_fPriorityLevel = 100;
	}



	// A* planner
	Planner aStarPlanner;
	try
	{
		std::vector<Action> the_plan = aStarPlanner.plan(_initialState, s_goalState, actions);
		std::vector<Action> steps;

		for (std::vector<Action>::reverse_iterator rit = the_plan.rbegin(); rit != the_plan.rend(); ++rit) {
			auto idx = std::distance(begin(the_plan), rit.base()) - 1;
			steps.push_back(the_plan.at(idx));
		}

		return steps;

	}
	catch (const std::exception&) {
		std::cout << "no path found for " << cTaskName << "\n";
	}

	return std::vector<Action>();
}

std::vector<Action> MuffinRecipe::PutMuffinsInCoolingRackByNum(State _initialState, const int _coolingRackNumFull, int _rackNum)
{

	// list of actions that could possibly occur in plan

	std::vector<Action> actions;
	const char* cTaskName = "Task: Placing Muffins into Cooling Rack";

	// actions

	Action a_moveToCoolingRack = Action("move to cooling rack", pricey);
	a_moveToCoolingRack.setPrecondition(atCoolingRack, false);
	a_moveToCoolingRack.setEffect(atPantry, false);
	a_moveToCoolingRack.setEffect(atFridge, false);
	a_moveToCoolingRack.setEffect(atMixer, false);
	a_moveToCoolingRack.setEffect(atSink, false);
	a_moveToCoolingRack.setEffect(atOven, false);
	a_moveToCoolingRack.setEffect(atCoolingRack, true);
	a_moveToCoolingRack.setEffect(atDisplayCase1, false);
	a_moveToCoolingRack.setEffect(atDisplayCase2, false);
	a_moveToCoolingRack.setEffect(atDisplayCase3, false);
	actions.push_back(a_moveToCoolingRack);

	if (_rackNum == 1) {
		Action a_placeMuffinsInCoolingRack1 = Action("place muffins on cooling rack 1", pricey);
		a_placeMuffinsInCoolingRack1.setPrecondition(atCoolingRack, true);
		a_placeMuffinsInCoolingRack1.setPrecondition(_coolingRackNumFull, false);
		a_placeMuffinsInCoolingRack1.setPrecondition(muffin_tray_contains_muffins, true);
		a_placeMuffinsInCoolingRack1.setEffect(_coolingRackNumFull, true);
		a_placeMuffinsInCoolingRack1.setEffect(muffin_tray_contains_muffins, false);
		actions.push_back(a_placeMuffinsInCoolingRack1);
	}
	else if (_rackNum == 2) {
		Action a_placeMuffinsInCoolingRack2 = Action("place muffins on cooling rack 2", pricey);
		a_placeMuffinsInCoolingRack2.setPrecondition(atCoolingRack, true);
		a_placeMuffinsInCoolingRack2.setPrecondition(_coolingRackNumFull, false);
		a_placeMuffinsInCoolingRack2.setPrecondition(muffin_tray_contains_muffins, true);
		a_placeMuffinsInCoolingRack2.setEffect(_coolingRackNumFull, true);
		a_placeMuffinsInCoolingRack2.setEffect(muffin_tray_contains_muffins, false);
		actions.push_back(a_placeMuffinsInCoolingRack2);
	}
	else if (_rackNum == 3) {
		Action a_placeMuffinsInCoolingRack3 = Action("place muffins on cooling rack 3", pricey);
		a_placeMuffinsInCoolingRack3.setPrecondition(atCoolingRack, true);
		a_placeMuffinsInCoolingRack3.setPrecondition(_coolingRackNumFull, false);
		a_placeMuffinsInCoolingRack3.setPrecondition(muffin_tray_contains_muffins, true);
		a_placeMuffinsInCoolingRack3.setEffect(_coolingRackNumFull, true);
		a_placeMuffinsInCoolingRack3.setEffect(muffin_tray_contains_muffins, false);
		actions.push_back(a_placeMuffinsInCoolingRack3);
	}
	

	// variables required to meet goal

	State s_goalState;
	s_goalState.setVariableById(_coolingRackNumFull, true);
	s_goalState.m_fPriorityLevel = 100;


	// A* planner
	Planner aStarPlanner;
	try
	{
		std::vector<Action> the_plan = aStarPlanner.plan(_initialState, s_goalState, actions);
		std::vector<Action> steps;

		for (std::vector<Action>::reverse_iterator rit = the_plan.rbegin(); rit != the_plan.rend(); ++rit) {
			auto idx = std::distance(begin(the_plan), rit.base()) - 1;
			steps.push_back(the_plan.at(idx));
		}

		return steps;

	}
	catch (const std::exception&) {
		std::cout << "no path found for " << cTaskName << "\n";
	}

	return std::vector<Action>();
}

std::vector<Action> MuffinRecipe::GetMuffinRecipe() {

	std::vector<Action> basic_plan = BasicPlan(currentWorldState);
	std::vector<Action> complete_plan;

	State tempWorldState = currentWorldState;
	for (auto& action : basic_plan)
	{
		std::cout << "\n\n";
		if (action.getName() == m_cMakeMuffinBatter) {
			std::vector<Action> steps = MakeMuffinBatter(tempWorldState);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cMakeMuffinBatter << std::endl;
		}
		if (action.getName() == m_cBakeMuffinsInOven) {
			std::vector<Action> steps = BakeMuffinsInOven(tempWorldState);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cBakeMuffinsInOven << std::endl;
		}
		if (action.getName() == m_cPutMuffinsOnRack1) {
			std::vector<Action> steps = PutMuffinsInCoolingRackByNum(tempWorldState, cooling_rack_1_is_full, 1);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutMuffinsOnRack1 << std::endl;
		}
		if (action.getName() == m_cPutMuffinsOnRack2) {
			std::vector<Action> steps = PutMuffinsInCoolingRackByNum(tempWorldState, cooling_rack_2_is_full, 2);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutMuffinsOnRack2 << std::endl;
		}
		if (action.getName() == m_cPutMuffinsOnRack3) {
			std::vector<Action> steps = PutMuffinsInCoolingRackByNum(tempWorldState, cooling_rack_3_is_full, 3);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutMuffinsOnRack3 << std::endl;
		}
		if (action.getName() == m_cPutWarmMuffinsInDisplay1) {
			std::vector<Action> steps = PutMuffinsInDisplayCaseByNumFromOven(tempWorldState, display_case_1_is_full, atDisplayCase1, 1);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutWarmMuffinsInDisplay1 << std::endl;
		}
		if (action.getName() == m_cPutWarmMuffinsInDisplay2) {
			std::vector<Action> steps = PutMuffinsInDisplayCaseByNumFromOven(tempWorldState, display_case_2_is_full, atDisplayCase2, 2);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutColdMuffinsInDisplay3FromRack3 << std::endl;
		}
		if (action.getName() == m_cPutWarmMuffinsInDisplay3) {
			std::vector<Action> steps = PutMuffinsInDisplayCaseByNumFromOven(tempWorldState, display_case_3_is_full, atDisplayCase3, 3);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutWarmMuffinsInDisplay3 << std::endl;
		}
		if (action.getName() == m_cPutColdMuffinsInDisplay1FromRack1) {
			std::vector<Action> steps = PlaceMuffinsInDisplayCaseFromRackByNum(tempWorldState, cooling_rack_1_is_full, 1, display_case_1_is_full, atDisplayCase1, 1);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutColdMuffinsInDisplay1FromRack1 << std::endl;
		}
		if (action.getName() == m_cPutColdMuffinsInDisplay1FromRack2) {
			std::vector<Action> steps = PlaceMuffinsInDisplayCaseFromRackByNum(tempWorldState, cooling_rack_2_is_full, 2, display_case_1_is_full, atDisplayCase1, 1);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutColdMuffinsInDisplay1FromRack2 << std::endl;
		}
		if (action.getName() == m_cPutColdMuffinsInDisplay1FromRack3) {
			std::vector<Action> steps = PlaceMuffinsInDisplayCaseFromRackByNum(tempWorldState, cooling_rack_3_is_full, 3, display_case_1_is_full, atDisplayCase1, 1);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutColdMuffinsInDisplay1FromRack3 << std::endl;
		}
		if (action.getName() == m_cPutColdMuffinsInDisplay2FromRack1) {
			std::vector<Action> steps = PlaceMuffinsInDisplayCaseFromRackByNum(tempWorldState, cooling_rack_1_is_full, 1, display_case_2_is_full, atDisplayCase2, 2);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutColdMuffinsInDisplay2FromRack1 << std::endl;
		}
		if (action.getName() == m_cPutColdMuffinsInDisplay2FromRack2) {
			std::vector<Action> steps = PlaceMuffinsInDisplayCaseFromRackByNum(tempWorldState, cooling_rack_2_is_full, 2, display_case_2_is_full, atDisplayCase2, 2);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutColdMuffinsInDisplay2FromRack2 << std::endl;
		}
		if (action.getName() == m_cPutColdMuffinsInDisplay2FromRack3) {
			std::vector<Action> steps = PlaceMuffinsInDisplayCaseFromRackByNum(tempWorldState, cooling_rack_3_is_full, 3, display_case_2_is_full, atDisplayCase2, 2);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutColdMuffinsInDisplay2FromRack3 << std::endl;
		}
		if (action.getName() == m_cPutColdMuffinsInDisplay3FromRack1) {
			std::vector<Action> steps = PlaceMuffinsInDisplayCaseFromRackByNum(tempWorldState, cooling_rack_1_is_full, 1, display_case_3_is_full, atDisplayCase3, 3);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutColdMuffinsInDisplay3FromRack1 << std::endl;
		}
		if (action.getName() == m_cPutColdMuffinsInDisplay3FromRack2) {
			std::vector<Action> steps = PlaceMuffinsInDisplayCaseFromRackByNum(tempWorldState, cooling_rack_2_is_full, 2, display_case_3_is_full, atDisplayCase3, 3);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutColdMuffinsInDisplay3FromRack2 << std::endl;
		}
		if (action.getName() == m_cPutColdMuffinsInDisplay3FromRack3) {
			std::vector<Action> steps = PlaceMuffinsInDisplayCaseFromRackByNum(tempWorldState, cooling_rack_3_is_full, 3, display_case_3_is_full, atDisplayCase3, 3);
			tempWorldState = PerformActionsOnState(steps, tempWorldState);
			complete_plan.insert(complete_plan.end(), steps.begin(), steps.end());
			std::cout << m_cPutColdMuffinsInDisplay3FromRack3 << std::endl;
		}
		std::cout << "\n";
	}

	return complete_plan;
}

int MuffinRecipe::GetTaskCost(std::vector<Action> _actions)
{
	int planCost = 0;
	for (auto& action : _actions)
	{
		//std::cout << "action name: " << action.getName() << "\n";
		planCost += action.getCost();
	}
	return planCost;
}

bool MuffinRecipe::DoPlansMatch(std::vector<Action> _actionsA, std::vector<Action> _actionsB)
{
	if (_actionsA.empty() && _actionsB.empty()) {
		std::cout << "both plans match because they're both empty\n";
		return true;
	}
	if (_actionsA.empty()) {
		std::cout << "plan a is empty\n";
		return false;
	}
	if (_actionsB.empty()) {
		std::cout << "plan b is empty\n";
		return false;
	}

	int a_to_b_margin = -1;
	int smaller_num = _actionsA.size() + a_to_b_margin < _actionsB.size() ? _actionsA.size() : _actionsB.size();

	for (int i = 0; i < smaller_num; i++) {
		if (_actionsA.at(i+ a_to_b_margin).getName() != _actionsB.at(i).getName()) {
			std::cout << "element " << i+ a_to_b_margin << " of plan a, does not have the same name as element " << i << " of plan b. plan a, element " << i+ a_to_b_margin << ": " << _actionsA.at(i+ a_to_b_margin).getName() << "!= plan b, element " << i << ": " << _actionsB.at(i).getName() << std::endl;
			return false;
		}
	}

	std::cout << "the plans match!\n";
	return true;
}


