#include "Hint.h"

Hint::Hint(QObject *parent) : QObject(parent)
{
    m_hintMessages[1] = "The one and only one";
    m_hintMessages[2] = "Two be or not two be";
    m_hintMessages[3] = "A triangle has three sides";
    m_hintMessages[4] = "Is this four me?";
}

QString Hint::getHint(const PuzzleState &currentState)
{
    PuzzleSolver solver(currentState);
    solver.solvePuzzle();

    unsigned hintTile = currentState.getTile(solver.getFirstMovedTile());

    return (m_hintMessages.find(hintTile) != m_hintMessages.end() ? m_hintMessages[hintTile] : "Move the " + QString::number(hintTile));
}
