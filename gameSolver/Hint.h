#ifndef HINT_H
#define HINT_H

#include <QObject>
#include <QString>

#include <map>

#include "gameLogic/PuzzleState.h"
#include "PuzzleSolver.h"

class Hint : public QObject
{
    Q_OBJECT
public:
    explicit Hint(QObject *parent = nullptr);

    QString getHint(const PuzzleState& currentState);

private:
    std::map<unsigned, QString> m_hintMessages;
};

#endif // HINT_H
