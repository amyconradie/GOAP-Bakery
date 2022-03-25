#ifndef STATE_H
#define STATE_H

#include "pch.h"

/*
    *State Struct*
    - m_fPriorityLevel:
    - m_cName:
    - m_mVariables:
    - setVariableById():
    - getVariableById():
    - matches():
    - getDistance():
    - '==': operator overloaded so that the m_mVariables are what is compared between States
*/
struct State {

    // Variables
    //-----------

    float m_fPriorityLevel;
    const char* m_cName;
    std::map<int, bool> m_mVariables;


    // Constructor
    //-------------

    State(const char* _cName = "");


    // Getters & Setters
    //-------------------

    void setVariableById(const int _iVariableId, const bool _bValue);
    bool getVariableById(const int _iVariableId) const;
    int getDistance(const State& _goalState) const;


    // Accessors
    //-----------

    bool matches(const State& _goalState) const;
    bool operator==(const State& _otherState) const;

};

#endif
