#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QMap>
#include <QPushButton>

#include <utility>

#include "PuzzleLogic.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(const QString& saveName, int difficulty, QWidget* mainWindow);
    ~GameWindow();

signals:
    //void undoClickSignal() const;
    //void redoClickSignal() const;
    void tileClickSignal(int index) const;
    void gameFinishSignal() const;

public slots:
    void updatePuzzleTiles(std::pair<unsigned, unsigned> tilePos, std::pair<unsigned, unsigned> emptyPos) const;
    void onGameFinish();
    void changeMovesCounter(unsigned moved) const;
    void setUndoButtonEnabled(bool) const;
    void setRedoButtonEnabled(bool) const;
    void updateTimer(QString newTime) const;

private:
    void setupUiSizes();
    void createButtons() const;

private:
    Ui::GameWindow* ui;
    PuzzleLogic*    m_puzzleLogic;
    QWidget*        m_mainWindow;
};

#endif // GAMEWINDOW_H
