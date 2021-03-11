#include "PuzzleLogic.h"
#include "GameWindow.h"

PuzzleLogic::PuzzleLogic() :
    m_moves(0),
    m_hints(0)
{
}

PuzzleLogic::PuzzleLogic(QWidget* parentWindow, unsigned grid, const QString& saveName) :
    m_gridSize(grid),
    m_moves(0),
    m_hints(0),
    m_currentState(PuzzleState::generateRandomState(grid)),
    m_currentGame(parentWindow),
    m_saveFile(new SaveFile(saveName))
{
    setupConnections();
}

PuzzleLogic::~PuzzleLogic()
{
    delete m_saveFile;
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

void PuzzleLogic::onGameTilePress(unsigned tileIndex)
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
        m_currentState = newState;
        m_moves++;

        std::pair<unsigned, unsigned> oldPosition = m_currentState.getGridFromArray(tileIndex);
        emit tileMovedSignal(oldPosition, newPosition, m_moves, m_currentState.isGoalState());
    }
}

void PuzzleLogic::setupConnections() const
{
    GameWindow* currentGame = qobject_cast<GameWindow*>(m_currentGame);
    connect(this, &PuzzleLogic::tileMovedSignal, currentGame, &GameWindow::updatePuzzleTiles);
    connect(this, &PuzzleLogic::gameFinish, currentGame, &GameWindow::onGameFinish);
}
