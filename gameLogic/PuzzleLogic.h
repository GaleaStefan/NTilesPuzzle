#ifndef PUZZLELOGIC_H
#define PUZZLELOGIC_H

#include "PuzzleState.h"
#include "handler/SaveFile.h"

#include <QWidget>

class PuzzleLogic : public QObject
{
    Q_OBJECT

public:
    PuzzleLogic();
    PuzzleLogic(QWidget* gameWindow);
    PuzzleLogic(QWidget* gameWindow, unsigned grid, const QString& saveName);
    virtual ~PuzzleLogic();

    unsigned    gridSize() const;
    void        setGridSize(const unsigned &gridSize);

    PuzzleState currentState() const;
    void        setCurrentState(const PuzzleState &currentState);

signals:
    void        tileMovedSignal(std::pair<unsigned, unsigned> tilePos, std::pair<unsigned, unsigned> emptyPos, int moves, bool finished) const;
    void        gameFinish() const;

public slots:
    void        onGameTilePress(unsigned tileIndex);

private:
    void        setupConnections() const;

private:
    unsigned    m_gridSize;
    unsigned    m_moves;
    unsigned    m_hints;

    PuzzleState m_currentState;
    QWidget*    m_currentGame;
    SaveFile*   m_saveFile;
};

#endif // PUZZLELOGIC_H
