#ifndef PUZZLELOGIC_H
#define PUZZLELOGIC_H

#include "PuzzleState.h"
#include "handler/SaveFile.h"

#include <QWidget>
#include <QTimerEvent>

#include <vector>

class PuzzleLogic : public QObject
{
    Q_OBJECT

public:
    PuzzleLogic(QWidget* gameWindow, unsigned grid, const QString& saveName);
    virtual ~PuzzleLogic();

    unsigned    gridSize() const;
    void        setGridSize(const unsigned &gridSize);

    PuzzleState currentState() const;

signals:
    void        tileMovedSignal(std::pair<unsigned, unsigned> tilePos, std::pair<unsigned, unsigned> emptyPos) const;
    void        movesChangedSignal(int moves) const;
    void        gameFinish() const;
    void        canUndoMove(bool) const;
    void        canRedoMove(bool) const;
    void        timerChange(QString time);

public slots:
    void        onGameTilePress(unsigned tileIndex);
    void        onSaveButtonPress();
    void        onUndoButtonPress();
    void        onRedoButtonPress();

protected:
    void        timerEvent(QTimerEvent* event);

private:
    void        setupConnections() const;
    void        handleTilesMove(std::pair<unsigned, unsigned> tilePos, std::pair<unsigned, unsigned> emptyPos);

private:
    unsigned                    m_gridSize;
    unsigned                    m_moves;
    unsigned                    m_hints;
    unsigned                    m_time;
    unsigned                    m_timerId;
    unsigned                    m_currentState;
    QWidget*                    m_currentGame;
    SaveFile*                   m_saveFile;
    std::vector<PuzzleState>    m_statesHistory;
};

#endif // PUZZLELOGIC_H
