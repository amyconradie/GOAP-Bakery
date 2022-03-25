#ifndef ACTION_H
#define ACTION_H

#include "State.h"
#include "pch.h"

// temp reference, needed to reassure the compiler that this struct exists
struct State;

/*
    *Action Class*
    - m_cName: 'human readable' name of action
    - m_iCost: cost of performing this action
    - m_mPreconditions: conditions inside a state need to have been met for this action to be performable
    - m_mEffects: results from performing this action on a state
    - canActOn(): returns true if the action can be acted on the input state
    - actOn(): return the state that results from performing the action on the input state
    - getCost(): return m_iCost
    - setPrecondition(): add a precondition required to perform the action
    - setEffect(): add effect that will be performed on a state
*/
class Action {

private:

    // Private Variables
    //-------------------

    const char* m_cName;
    int m_iCost;
    

public:

    std::unordered_map<int, bool> m_mPreconditions;
    std::unordered_map<int, bool> m_mEffects;

    // Constructors
    //--------------

    Action();
    Action(const char* _cName, int _iCost);


    // Action Functions
    //------------------

    bool canBePerformedOnState(const State& _state) const;
    State performOnState(const State& _state) const;


    // Getters & Setters
    //-------------------

    int getCost() const;
    const char* getName() const;
    void setPrecondition(const int _key, const bool _value);
    void setEffect(const int _key, const bool _value);

};

#endif