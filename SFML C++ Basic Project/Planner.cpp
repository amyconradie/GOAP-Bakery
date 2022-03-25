#include "Planner.h"

Planner::Planner()
{
    this->sEndState = State();
}

int Planner::calcHeuristic(const State& _currentState, const State& _goalState) const
{
    return _currentState.getDistance(_goalState);
}

void Planner::openNode(Node&& _n)
{
    // search the m_vOpenNodesList list for the first node that has a fCost greater than _n.calcFCost()
    std::vector<Node>::iterator greaterNode = std::lower_bound(begin(m_vOpenNodesList), end(m_vOpenNodesList), _n);

    // move _n to just before the first node found with a greater fCostthat node
    m_vOpenNodesList.emplace(greaterNode, std::move(_n));
}

Node& Planner::closeNode()
{
    // check that the openNodesList is not empty
    if (!m_vOpenNodesList.empty()) {

        // add to the closedNodesList
        m_vClosedNodesList.push_back(std::move(m_vOpenNodesList.front()));

        // remove fromt the  openNodesList
        m_vOpenNodesList.erase(m_vOpenNodesList.begin());

        // return this node by getting it from the end of the closedNodesList
        return m_vClosedNodesList.back();
    }
    else {
        // if the m_vOpenNodesList is empty something went horribly wrong to get us here
        std::cout << "Error closing a node: m_vOpenNodesList is empty and it isn't supposed to be\n";
        abort(); // end the program
    }
}

bool Planner::isClosed(const State& _state) const
{
    // check to see if the state has already been assessed and is present in the closedNodesList
    if (std::find_if(
        begin(m_vClosedNodesList),
        end(m_vClosedNodesList),
        [&](const Node& n) { return n.m_state == _state; }) == end(m_vClosedNodesList))
    {
        return false;
    }

    return true;
}

std::vector<Node>::iterator Planner::isOpen(const State& _state)
{
    // check to see if the state has not been assessed and is present in the openNodesList
    // and if so return the node with the matching state
    return std::find_if(
        begin(m_vOpenNodesList),
        end(m_vOpenNodesList),
        [&](const Node& n) { return n.m_state == _state; });
}

void Planner::printOpenList() const {
    for (const auto& n : m_vOpenNodesList) {
        std::cout << "Node { id:" << n.m_iId << " parent:" << n.m_iParentId << " F:" << n.calcFCost() << " G:" << n.m_iGCost << " H:" << n.m_iHCost << ", state: " << n.m_state.m_cName << "}\n";
    }
}

void Planner::printClosedList() const {
    for (const auto& n : m_vClosedNodesList) {
        std::cout << "Node { id:" << n.m_iId << " parent:" << n.m_iParentId << " F:" << n.calcFCost() << " G:" << n.m_iGCost << " H:" << n.m_iHCost << ", state: " << n.m_state.m_cName << "}\n";
    }
}

State Planner::getEndState()
{
    if (!sEndState.m_mVariables.empty()) {
        return this->sEndState;
    }
    else {
        return State();
    }
}

std::vector<Action> Planner::plan(const State& _startState, const State& _goalState, const std::vector<Action>& _actions)
{
    // check that the startState != goalState
    if (_startState.matches(_goalState))
    {
        std::cout << "startState is the same as the goalState \n";
        return std::vector<Action>();
    }

    // make sure open and closed node lists are empty
    // (for if this instance of the planner has already been used)
    m_vOpenNodesList.clear();
    m_vClosedNodesList.clear();

    //printClosedList();
    //printOpenList();

    // create the starting node
    // add it to the OpenNodeslist
    Node startNode = Node(_startState, 0, calcHeuristic(_startState, _goalState), 0, nullptr);
    m_vOpenNodesList.push_back(std::move(startNode));

    // while there are unsearched nodes
    while (m_vOpenNodesList.size() > 0)
    {
        // close the first item in the openNodesList
        // set that node as the current node
        Node& currentNode = closeNode();

        // check if the currentNode's state matches the the goalState
        // if all the variables have the same keys and the expected true/false values
        if (currentNode.m_state.matches(_goalState))
        {
            this->sEndState = currentNode.m_state;

            // creates a list of actions in the order they need to be performed
            std::vector<Action> vPlan;

            do {
                // add the action required by the current node to the plan
                vPlan.push_back(*currentNode.m_action);

                // find the currentNode's parent
                std::vector<Node>::iterator parentNode = std::find_if(
                    begin(m_vOpenNodesList),
                    end(m_vOpenNodesList),
                    [&](const Node& n) {
                        return n.m_iId == currentNode.m_iParentId;
                    }
                );

                // if the parentNode is not in the openNodesList
                if (parentNode == end(m_vOpenNodesList))
                {
                    // find the parentNode in the closedNodesList
                    parentNode = std::find_if(
                        begin(m_vClosedNodesList),
                        end(m_vClosedNodesList),
                        [&](const Node& n) {
                            return n.m_iId == currentNode.m_iParentId;
                        }
                    );
                }

                // set the currentNode to the parentNode
                currentNode = *parentNode;
            } while (currentNode.m_iParentId != 0); // keep going until a parentless node is found

            // return the list of actions required to reach the goalState from the currentState
            return vPlan;
        }

        // go through the list of actions provided
        for (const auto& possibleAction : _actions)
        {
            // see if the action can be performed on the currentNode's state
            if (possibleAction.canBePerformedOnState(currentNode.m_state))
            {
                // the result of performing this action acction on the currentNode's state
                State resultState = possibleAction.performOnState(currentNode.m_state);

                // see if the resultState of performing this action matches the state of an existing node that has already been assessed
                // if so move onto the next possibleAction
                if (isClosed(resultState))
                {
                    continue;
                }

                // see if an existing unassessed node's state matches the resultState
                std::vector<Node>::iterator resultNode = isOpen(resultState);

                // see if the resultNode is not in the openNodesList
                if (resultNode == end(m_vOpenNodesList))
                {
                    // create a new node with currentNode as the parent
                    // and add the cost of performing the possibleAction added to the gCost
                    Node childNode = Node(resultState, currentNode.m_iGCost + possibleAction.getCost(), calcHeuristic(resultState, _goalState), currentNode.m_iId, &possibleAction);

                    // add the childNode to the openNodesList
                    openNode(std::move(childNode));
                }
                else // is in the openNodesList
                {
                    // check if current gCost is cheaper than recorded gCost
                    if (currentNode.m_iGCost + possibleAction.getCost() < resultNode->m_iGCost)
                    {
                        resultNode->m_iParentId = currentNode.m_iId; // set currentid as the parentId
                        resultNode->m_iGCost = currentNode.m_iGCost + possibleAction.getCost(); // add cost of performing possibleAction to the gCost
                        resultNode->m_iHCost = calcHeuristic(resultState, _goalState); // get hCost of moving from this state to the goalState
                        resultNode->m_action = &possibleAction; // set possibleAction as the node's action

                        // sort openNodesList by fCost
                        std::sort(begin(m_vOpenNodesList), end(m_vOpenNodesList));
                    }
                }
            }
        }
    }
}
