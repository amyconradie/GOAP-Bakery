#ifndef PLANNER_H
#define PLANNER_H

#include "Action.h"
#include "Node.h"
#include "State.h"

#include "pch.h"

/*
    *Planner Class*
    - m_vOpenNodesList: list of nodes that have yet to be assessed
    - m_vClosedNodesList: list of nodes that have already been assessed
    - isClosed(): returns true if node is in the closedList
    - isOpen(): returns true if node is in the openList
    - closeNode(): remove node from openList and add to closedList
    - openNode(): add node to openList
    - calcHeuristic(): get distance between two states
    - plan(): returns a plan based on a start state, goal state and a list of actions
*/
class Planner
{

private:

    // Private Variables
    //-------------------

    std::vector<Node> m_vOpenNodesList;
    std::vector<Node> m_vClosedNodesList;
    State sEndState;
    bool isClosed(const State& _state) const;
    std::vector<Node>::iterator isOpen(const State& _state);
    void printOpenList() const;
    Node& closeNode();
    void openNode(Node&& _n);
    int calcHeuristic(const State& _currentState, const State& _goalState) const;

public:

    // Constructor
    //-------------

    Planner();


    // Planner Function
    //------------------

    void printClosedList() const;
    State getEndState();
    std::vector<Action> plan(const State& _startState, const State& _goalState, const std::vector<Action>& _actions);

};

#endif
