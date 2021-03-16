#include <QDialog>

#include "PuzzleLogic.h"
#include "GameWindow.h"

PuzzleLogic::PuzzleLogic(QWidget* parentWindow, unsigned grid, const QString& saveName) :
    m_timerId(startTimer(1000)),
    m_currentGame(parentWindow),
    m_saveFile(new SaveFile(saveName)),
    m_hintManager(new Hint(this))
{

    m_gameData = new SaveData {0, 0, 0, grid, 0, std::vector<PuzzleState>()};
    m_gameData->m_history.push_back(PuzzleState::generateRandomState(grid));
    setupConnections();
}

PuzzleLogic::PuzzleLogic(QWidget *gameWindow, const QString &saveName) :
    m_currentGame(gameWindow),
    m_saveFile(new SaveFile(saveName)),
    m_hintManager(new Hint(this))
{
    m_gameData = m_saveFile->loadGame();
    m_timerId = startTimer(1000);

    setupConnections();

    emit movesChangedSignal(m_gameData->m_moves);
    emit canUndoMove(m_gameData->m_state != 0);
    emit canRedoMove(m_gameData->m_state < m_gameData->m_history.size() - 1);
}

PuzzleLogic::~PuzzleLogic()
{
    delete m_saveFile;
    delete m_gameData;
    killTimer(m_timerId);
}

void PuzzleLogic::saveGame() const
{
    m_saveFile->saveGame(m_gameData);
}

unsigned PuzzleLogic::gridSize() const
{
    return m_gameData->m_grid;
}

void PuzzleLogic::setGridSize(const unsigned &gridSize)
{
    m_gameData->m_grid = gridSize;
}

PuzzleState PuzzleLogic::currentState() const
{
    return m_gameData->m_history[m_gameData->m_state];
}

void PuzzleLogic::onGameTilePress(unsigned tileIndex)
{
    bool canBeMoved;
    std::pair<unsigned, unsigned> newPosition = m_gameData->m_history[m_gameData->m_state].attemptMove(tileIndex, canBeMoved);

    if(canBeMoved)
    {
        if(m_gameData->m_state < m_gameData->m_history.size() - 1)
        {
            m_gameData->m_history.erase(m_gameData->m_history.begin() + m_gameData->m_state, m_gameData->m_history.end());
        }

        PuzzleState newState(m_gameData->m_history[m_gameData->m_state]);
        newState.swapTiles(tileIndex, newPosition.first * m_gameData->m_grid + newPosition.second);
        m_gameData->m_history.push_back(newState);

        m_gameData->m_state++;

        std::pair<unsigned, unsigned> oldPosition = m_gameData->m_history[m_gameData->m_state].getGridFromArray(tileIndex);
        handleTilesMove(oldPosition, newPosition);
    }
}

void PuzzleLogic::onSaveButtonPress()
{
    m_saveFile->saveGame(m_gameData);
    //m_currentGame->close();
}

void PuzzleLogic::onUndoButtonPress()
{
    assert(m_gameData->m_state > 0);

    unsigned oldEmptyPos = m_gameData->m_history[m_gameData->m_state - 1].getIndex(0);
    unsigned currentEmptyPos = m_gameData->m_history[m_gameData->m_state].getIndex(0);

    std::pair<unsigned, unsigned> oldPos {oldEmptyPos / m_gameData->m_grid, oldEmptyPos % m_gameData->m_grid};
    std::pair<unsigned, unsigned> newPos {currentEmptyPos / m_gameData->m_grid, currentEmptyPos % m_gameData->m_grid};

    m_gameData->m_state--;

    handleTilesMove(oldPos, newPos);
}

void PuzzleLogic::onRedoButtonPress()
{
    assert(m_gameData->m_state < m_gameData->m_history.size() - 1);

    unsigned oldEmptyPos = m_gameData->m_history[m_gameData->m_state + 1].getIndex(0);
    unsigned currentEmptyPos = m_gameData->m_history[m_gameData->m_state].getIndex(0);

    std::pair<unsigned, unsigned> oldPos {oldEmptyPos / m_gameData->m_grid, oldEmptyPos % m_gameData->m_grid};
    std::pair<unsigned, unsigned> newPos {currentEmptyPos / m_gameData->m_grid, currentEmptyPos % m_gameData->m_grid};

    m_gameData->m_state++;

    handleTilesMove(oldPos, newPos);
}

void PuzzleLogic::onHintButtonPress()
{
    QString hint = m_hintManager->getHint(m_gameData->m_history[m_gameData->m_state]);
    m_gameData->m_hints++;
    emit hintRequest();

    GameWindow* currentGame = qobject_cast<GameWindow*>(m_currentGame);

    QDialog* dialog = new QDialog(currentGame);
    dialog->setWindowTitle("HINT");
    dialog->show();
    dialog->exec();
    dialog->close();
}

void PuzzleLogic::timerEvent(QTimerEvent *event)
{
    m_gameData->m_time++;

    int seconds = m_gameData->m_time % 60;
    int minutes = (m_gameData->m_time / 60) % 60;
    int hours = (m_gameData->m_time / 60 / 60);

    QString time = QString("%1:%2:%3").arg(hours, 2, 10, QChar('0'))
                                      .arg(minutes, 2, 10, QChar('0'))
                                      .arg(seconds, 2, 10, QChar('0'));

    emit timerChange(time);
}

void PuzzleLogic::handleTilesMove(std::pair<unsigned, unsigned> tilePos, std::pair<unsigned, unsigned> emptyPos)
{
    m_gameData->m_moves++;

    emit tileMovedSignal(tilePos, emptyPos);
    emit movesChangedSignal(m_gameData->m_moves);
    emit canUndoMove(m_gameData->m_state != 0);
    emit canRedoMove(m_gameData->m_state < m_gameData->m_history.size() - 1);

    if(m_gameData->m_history[m_gameData->m_state].isGoalState())
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
