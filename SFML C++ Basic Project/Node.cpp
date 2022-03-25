#include "Node.h"

int Node::m_iLastIdGenerated = 0;

Node::Node() {
    m_iGCost = 0;
    m_iHCost = 0;
    m_iId = ++m_iLastIdGenerated;
}

Node::Node(const State _state, int _iGCost, int _iHCost, int _iParentId, const Action* _action)
{
    m_state = _state;
    m_iGCost = _iGCost;
    m_iHCost = _iHCost;
    m_iParentId = _iParentId;
    m_action = _action;
    m_iId = ++m_iLastIdGenerated; // increase most recently generated ID by 1
}

int Node::calcFCost() const
{
    return m_iGCost + m_iHCost;
}

bool operator<(const Node& _nLeftHandNode, const Node& _nRightHandNode) {
    return _nLeftHandNode.calcFCost() < _nRightHandNode.calcFCost();
}
