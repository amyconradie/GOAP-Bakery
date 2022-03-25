#include "State.h"
#include "State.h"

State::State(const char* name)
{
    m_fPriorityLevel = 0;
    m_cName = name;
}

void State::setVariableById(const int _iVariableId, const bool _bValue)
{
    m_mVariables[_iVariableId] = _bValue;
}

bool State::getVariableById(const int _iVariableId) const {
    return m_mVariables.at(_iVariableId);
}

bool State::operator==(const State& _otherState) const
{
    return (m_mVariables == _otherState.m_mVariables);
}

bool State::matches(const State& _goalState) const
{

    // if any variables do not match the expected variables in the goalState, return false
    for (const auto& mCurrentVariable : _goalState.m_mVariables)
    {
        try {
            // find variable by it's unique key
            // if the variables value does not match the expected value, return false
            if (m_mVariables.at(mCurrentVariable.first) != mCurrentVariable.second)
            {
                return false;
            }
        }
        catch (const std::out_of_range&) { // in case foreach loop goes out of bounds
            return false;
        }
    }
    return true;
}

int State::getDistance(const State& _goalState) const
{
    // steps required to reach the goalState
    int iDistance = 0;

    // go through each variable in the goalState 
    for (const auto& mCurrentVariable : _goalState.m_mVariables)
    {
        // look for the variable in this state that matches the currentVariable
        auto mTemp = m_mVariables.find(mCurrentVariable.first);

        // if the matching variable is not the final variable in this state's variables
        // increase the distance required to reach this state
        if (mTemp == end(m_mVariables) || mTemp->second != mCurrentVariable.second)
        {
            // increase the number of steps required by 1
            ++iDistance;
        }
    }

    // return number of steps required to reach the goal state from this state
    return iDistance;
}