#include "SolverNode.h"

SolverNode::SolverNode() :
    m_treeLevel(0),
    m_cost(0),
    m_state(SolverState(0, std::vector<unsigned>(0))),
    m_parent(nullptr),
    m_nodeAction(eAction::NONE)
{
}

SolverNode::SolverNode(const SolverState &state, SolverNode *parent, eAction action) :
    m_state(state),
    m_parent(parent),
    m_nodeAction(action)
{
    m_treeLevel = (parent == nullptr) ? 0 : parent->m_treeLevel + 1;
    m_cost = m_state.getManhattanDistance() + m_treeLevel;
}

/*
SolverNode::SolverNode(const SolverNode &other)
{
    m_treeLevel = other.m_treeLevel;
    m_cost = other.m_cost;
    m_state = other.m_state;
    m_nodeAction = other.m_nodeAction;

    if(other.m_parent != nullptr)
    {
        m_parent = new SolverNode(other.m_state, other.m_parent, other.m_nodeAction);
    }
}
*/

SolverNode::~SolverNode()
{
    if(m_parent != nullptr)
    {
        delete  m_parent;
        m_parent = nullptr;
    }
}


bool SolverNode::operator<(const SolverNode &other) const
{
    return !(m_cost < other.cost());
}

unsigned SolverNode::treeLevel() const
{
    return m_treeLevel;
}

void SolverNode::setTreeLevel(unsigned treeLevel)
{
    m_treeLevel = treeLevel;
}

unsigned SolverNode::cost() const
{
    return m_cost;
}

void SolverNode::setCost(unsigned cost)
{
    m_cost = cost;
}

SolverState SolverNode::state() const
{
    return m_state;
}

void SolverNode::setState(const SolverState &state)
{
    m_state = state;
}

SolverNode *SolverNode::parentNode() const
{
    return m_parent;
}

void SolverNode::setParentNode(SolverNode *parentNode)
{
    m_parent = parentNode;
}

eAction SolverNode::nodeAction() const
{
    return m_nodeAction;
}

void SolverNode::setNodeAction(const eAction &nodeAction)
{
    m_nodeAction = nodeAction;
}
