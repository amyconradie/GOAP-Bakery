#ifndef NODE_H
#define NODE_H

#include "Action.h"
#include "State.h"
#include "pch.h"

/*
    *Node Struct*
    - ids:
      -- m_iId: this node's unique Id
      -- m_iParentId: parentNode's unique id
      -- m_iLastIdGenerated: increments each time a new node is created/constructed
    - costs:
      -- m_iGCost: trip from startNode to thisNode
      -- m_iHCost: trip from thisNode to goalNode
      -- calcFCost():
    - m_state: current state when this node is reached
    - action: pointer to the action assigned to this node
    - '<': operator overloaded for functions that sort vectors
*/
struct Node {

    // Variables
    //-----------

    static int m_iLastIdGenerated;
    State m_state;
    int m_iParentId;
    int m_iGCost;
    int m_iHCost;
    const Action* m_action;
    int m_iId;


    // Constructors
    //--------------

    Node();
    Node(const State _state, int _iGCost, int _iHCost, int _iParentId, const Action* _action);


    // A* Functions
    //--------------

        // returns the total cost of achieving goal if traversing through this node
        // gCost (startNode to thisNode) + hCost (thisNode to goalNode) = fCost (totalCost)
    int calcFCost() const;


};

// VERY IMPORTANT!! for using SORT, LOWER_BOUNDS and UPPER_BOUNDS vector sorting functions
// operator overloading, allows us to compare our custom nodes object using vector functions
bool operator<(const Node& _nLeftHandNode, const Node& _nRightHandNode);

#endif