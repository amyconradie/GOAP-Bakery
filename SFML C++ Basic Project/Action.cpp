#include "Action.h"

Action::Action()
{
    m_iCost = 0;
    m_cName = "";
}

Action::Action(const char* _cName, int _iCost)
{
    m_cName = _cName;
    m_iCost = _iCost;
}

bool Action::canBePerformedOnState(const State& _state) const
{
    // go through the list of preconditions required to perform this action
    // if any of the input state's variables fail to match the preconditions, return false
    for (const auto& precondition : m_mPreconditions) {
        try {
            // find the precondition by it's unique key
            // if the precondition has not been met (is false) return false
            if (_state.m_mVariables.at(precondition.first) != precondition.second)
            {
                return false;
            }
        }
        catch (const std::out_of_range&) { // in case the foreach loop goes out of bounds
            return false;
        }
    }
    return true;
}

State Action::performOnState(const State& _state) const
{
    // create a new state based on the input state
    State tempState = State(_state);

    // apply this Action's effects onto that state
    for (const auto& effect : m_mEffects) {
        tempState.setVariableById(effect.first, effect.second);
    }

    return tempState;
}

void Action::setPrecondition(const int _key, const bool _value)
{
    // create a new precondition by adding a unique key and a assigning it a true/false value
    m_mPreconditions[_key] = _value;
}

void Action::setEffect(const int _key, const bool _value)
{
    // create a new effect by adding a unique key and a assigning it a true/false value
    m_mEffects[_key] = _value;
}

int Action::getCost() const
{
    return m_iCost;
}

const char* Action::getName() const
{
    return m_cName;
}