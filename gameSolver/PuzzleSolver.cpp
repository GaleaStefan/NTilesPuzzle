#include "PuzzleSolver.h"
#include "eAction.h"

PuzzleSolver::PuzzleSolver(const PuzzleState& state)
{
    m_initialState = SolverState(state.getMatrixSize(), state.getState());

    //connect(this, &PuzzleSolver::puzzleSolved, this, &PuzzleSolver::testSolve);
}

void PuzzleSolver::solvePuzzle()
{
    SolverNode firstNode(m_initialState, nullptr, eAction::NONE);
    m_openNodes.push(firstNode);

    while(true)
    {
        if(m_openNodes.empty())
        {
            //throw error
            return;
        }

        SolverNode currentNode(m_openNodes.top());
        m_openNodes.pop();


        if(currentNode.state().isGoalState())
        {
            m_goalNode = currentNode;
            return;
        }

        generateChildren(currentNode);

        delete currentNode.parentNode();
    }
}

unsigned PuzzleSolver::getFirstMovedTile()
{
    SolverNode* node = &m_goalNode;

    while(node != nullptr)
    {
        m_solutionNodes.push(node);
        node = node->parentNode();
    }

    m_solutionNodes.pop();

    return m_solutionNodes.top()->state().getIndex(0);
}

void PuzzleSolver::generateChildren(SolverNode node)
{
    const std::vector<std::pair<unsigned, unsigned>> neighbours {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1}
    };

    unsigned gridSize = node.state().getMatrixSize();
    std::pair<unsigned, unsigned> emptyTile = SolverState::getGridPosition(node.state().getIndex(0), gridSize);

    for(unsigned index = 0; index < 4; index++)
    {

        std::pair<int, int> neighbour {(int)emptyTile.first + neighbours[index].first, (int)emptyTile.second + neighbours[index].second};

        if(neighbour.first >= 0 && neighbour.first < (int)gridSize &&
           neighbour.second >= 0 && neighbour.second < (int)gridSize &&
           eAction(index) != node.nodeAction() )
        {
            SolverState newState = node.state().swap(emptyTile, {(unsigned)neighbour.first, (unsigned)neighbour.second});

            if(m_exploredNodes.find(newState) == m_exploredNodes.end())
            {
                SolverNode child(newState, new SolverNode(node), eAction(index));
                m_exploredNodes[newState] = true;
                m_openNodes.push(child);
            }
        }
    }
}
