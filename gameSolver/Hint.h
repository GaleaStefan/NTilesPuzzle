#ifndef HINT_H
#define HINT_H

#include <QObject>

#include "gameLogic/PuzzleState.h"

class Hint : public QObject
{
    Q_OBJECT
public:
    explicit Hint(QObject *parent = nullptr);

    QString getHint(const PuzzleState& currentState);
};

#endif // HINT_H
