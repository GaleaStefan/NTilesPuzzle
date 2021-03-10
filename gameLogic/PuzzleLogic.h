#ifndef PUZZLELOGIC_H
#define PUZZLELOGIC_H

#include "PuzzleState.h"
#include <QWidget>

class PuzzleLogic
{
public:
    PuzzleLogic();
    PuzzleLogic(QWidget* gameWindow);
    PuzzleLogic(QWidget* gameWindow, unsigned grid);

    unsigned gridSize() const;
    void setGridSize(const unsigned &gridSize);

    PuzzleState currentState() const;
    void setCurrentState(const PuzzleState &currentState);
    void handleTilePress(unsigned tileIndex);
private:
    unsigned m_gridSize;
    unsigned m_moves;
    unsigned m_hints;

    PuzzleState m_currentState;
    QWidget* m_currentGame;
};

#endif // PUZZLELOGIC_H
