#include "PuzzleLogic.h"
#include "GameWindow.h"

PuzzleLogic::PuzzleLogic() :
    m_moves(0),
    m_hints(0)
{
}

PuzzleLogic::PuzzleLogic(QWidget* parentWindow) :
    m_moves(0),
    m_hints(0),
    m_currentGame(parentWindow)
{
}

PuzzleLogic::PuzzleLogic(QWidget* parentWindow, unsigned grid) :
    m_gridSize(grid),
    m_moves(0),
    m_hints(0),
    m_currentState(PuzzleState::generateRandomState(grid)),
    m_currentGame(parentWindow)
{
}

unsigned PuzzleLogic::gridSize() const
{
    return m_gridSize;
}

void PuzzleLogic::setGridSize(const unsigned &gridSize)
{
    m_gridSize = gridSize;
}

PuzzleState PuzzleLogic::currentState() const
{
    return m_currentState;
}

void PuzzleLogic::setCurrentState(const PuzzleState &currentState)
{
    m_currentState = currentState;
}

void PuzzleLogic::handleTilePress(unsigned tileIndex)
{
    if(m_currentState.getTile(tileIndex) == 0)
    {
        return;
    }

    bool canBeMoved;
    std::pair<unsigned, unsigned> newPosition = m_currentState.attemptMove(tileIndex, canBeMoved);

    if(canBeMoved)
    {
        PuzzleState newState(m_currentState);
        newState.swapTiles(tileIndex, newPosition.first * m_gridSize + newPosition.second);

        this->m_currentState = newState;

        GameWindow* window = qobject_cast<GameWindow*>(m_currentGame);
        window->updatePuzzleTiles(m_currentState.getGridFromArray(tileIndex), newPosition);
    }
}
