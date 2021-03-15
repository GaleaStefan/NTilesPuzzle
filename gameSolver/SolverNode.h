#ifndef SOLVERNODE_H
#define SOLVERNODE_H

#include "SolverState.h"
#include "eAction.h"

class SolverNode
{
public:
    SolverNode();
    SolverNode(const SolverState& state, SolverNode* parent, eAction action);
    //SolverNode(const SolverNode& other);
    ~SolverNode();

    bool        operator<(const SolverNode& other) const;

    unsigned    treeLevel() const;
    void        setTreeLevel(unsigned treeLevel);

    unsigned    cost() const;
    void        setCost(unsigned cost);

    SolverState state() const;
    void        setState(const SolverState &state);

    SolverNode* parentNode() const;
    void        setParentNode(SolverNode* parentNode);

    eAction     nodeAction() const;
    void        setNodeAction(const eAction &nodeAction);

private:
    unsigned    m_treeLevel;
    unsigned    m_cost;
    SolverState m_state;
    SolverNode* m_parent;
    eAction     m_nodeAction;
};

#endif // SOLVERNODE_H
