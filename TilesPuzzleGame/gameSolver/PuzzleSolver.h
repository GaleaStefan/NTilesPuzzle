#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include "gameLogic/PuzzleState.h"
#include "SolverState.h"
#include "SolverNode.h"

#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>

#include <QObject>

class PuzzleSolver : public QObject
{
    Q_OBJECT

public:
    PuzzleSolver(const PuzzleState& initialState);

    void        solvePuzzle();
    unsigned    getFirstMovedTile();

private:
    void        generateChildren(SolverNode node);

private:
    SolverState                                                             m_initialState;
    SolverNode                                                              m_goalNode;
    std::unordered_map<SolverState, bool, std::hash<SolverState>>           m_exploredNodes;
    std::priority_queue<SolverNode,
                        std::vector<SolverNode>,
                        std::less<std::vector<SolverNode>::value_type>>     m_openNodes;

    std::stack<SolverNode*>                                                 m_solutionNodes;
};

#endif // PUZZLESOLVER_H
