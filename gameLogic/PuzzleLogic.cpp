#include "PuzzleLogic.h"
#include "GameWindow.h"

PuzzleLogic::PuzzleLogic(QWidget* parentWindow, unsigned grid, const QString& saveName) :
    m_gridSize(grid),
    m_moves(0),
    m_hints(0),
    m_time(0),
    m_timerId(startTimer(1000)),
    m_currentState(0),
    m_currentGame(parentWindow),
    m_saveFile(new SaveFile(saveName))
{


    m_statesHistory.push_back(PuzzleState::generateRandomState(grid));
    setupConnections();
}

PuzzleLogic::~PuzzleLogic()
{
    delete m_saveFile;
    killTimer(m_timerId);
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
    return m_statesHistory[m_currentState];
}

void PuzzleLogic::onGameTilePress(unsigned tileIndex)
{
    bool canBeMoved;
    std::pair<unsigned, unsigned> newPosition = m_statesHistory[m_currentState].attemptMove(tileIndex, canBeMoved);

    if(canBeMoved)
    {
        if(m_currentState < m_statesHistory.size() - 1)
        {
            m_statesHistory.erase(m_statesHistory.begin() + m_currentState, m_statesHistory.end());
        }

        PuzzleState newState(m_statesHistory[m_currentState]);
        newState.swapTiles(tileIndex, newPosition.first * m_gridSize + newPosition.second);
        m_statesHistory.push_back(newState);

        m_currentState++;

        std::pair<unsigned, unsigned> oldPosition = m_statesHistory[m_currentState].getGridFromArray(tileIndex);
        handleTilesMove(oldPosition, newPosition);
    }
}

void PuzzleLogic::onSaveButtonPress()
{
    m_saveFile->saveGame(m_gridSize, m_moves, m_hints, m_time, m_currentState, m_statesHistory);
}

void PuzzleLogic::onUndoButtonPress()
{
    assert(m_currentState > 0);

    unsigned oldEmptyPos = m_statesHistory[m_currentState - 1].getIndex(0);
    unsigned currentEmptyPos = m_statesHistory[m_currentState].getIndex(0);

    std::pair<unsigned, unsigned> oldPos {oldEmptyPos / m_gridSize, oldEmptyPos % m_gridSize};
    std::pair<unsigned, unsigned> newPos {currentEmptyPos / m_gridSize, currentEmptyPos % m_gridSize};

    m_currentState--;

    handleTilesMove(oldPos, newPos);
}

void PuzzleLogic::onRedoButtonPress()
{
    assert(m_currentState < m_statesHistory.size() - 1);

    unsigned oldEmptyPos = m_statesHistory[m_currentState + 1].getIndex(0);
    unsigned currentEmptyPos = m_statesHistory[m_currentState].getIndex(0);

    std::pair<unsigned, unsigned> oldPos {oldEmptyPos / m_gridSize, oldEmptyPos % m_gridSize};
    std::pair<unsigned, unsigned> newPos {currentEmptyPos / m_gridSize, currentEmptyPos % m_gridSize};

    m_currentState++;

    handleTilesMove(oldPos, newPos);
}

void PuzzleLogic::timerEvent(QTimerEvent *event)
{
    m_time++;

    int seconds = m_time % 60;
    int minutes = (m_time / 60) % 60;
    int hours = (m_time / 60 / 60);

    QString time = QString("%1:%2:%3").arg(hours, 2, 10, QChar('0'))
                                      .arg(minutes, 2, 10, QChar('0'))
                                      .arg(seconds, 2, 10, QChar('0'));

    emit timerChange(time);
}

void PuzzleLogic::handleTilesMove(std::pair<unsigned, unsigned> tilePos, std::pair<unsigned, unsigned> emptyPos)
{
    m_moves++;

    emit tileMovedSignal(tilePos, emptyPos);
    emit movesChangedSignal(m_moves);
    emit canUndoMove(m_currentState != 0);
    emit canRedoMove(m_currentState < m_statesHistory.size() - 1);

    if(m_statesHistory[m_currentState].isGoalState())
    {
        emit gameFinish();
    }
}

void PuzzleLogic::setupConnections() const
{
    GameWindow* currentGame = qobject_cast<GameWindow*>(m_currentGame);

    connect(this, &PuzzleLogic::tileMovedSignal, currentGame, &GameWindow::updatePuzzleTiles);
    connect(this, &PuzzleLogic::gameFinish, currentGame, &GameWindow::onGameFinish);
    connect(this, &PuzzleLogic::movesChangedSignal, currentGame, &GameWindow::changeMovesCounter);
    connect(this, &PuzzleLogic::canUndoMove, currentGame, &GameWindow::setUndoButtonEnabled);
    connect(this, &PuzzleLogic::canRedoMove, currentGame, &GameWindow::setRedoButtonEnabled);
    connect(this, &PuzzleLogic::timerChange, currentGame, &GameWindow::updateTimer);
}
