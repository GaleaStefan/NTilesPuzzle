#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QMap>
#include <QPushButton>
#include <QCloseEvent>

#include <utility>

#include "PuzzleLogic.h"
#include "gameSolver/HintDialog.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(const QString& saveName, int difficulty, QWidget* mainWindow); // for new games
    explicit GameWindow(const QString& saveName, QWidget* mainWindow); // for game load
    ~GameWindow();

    void enableHintButton() const;

signals:
    void tileClickSignal(int index) const;
    void gameFinishSignal() const;
    void windowCloseSignal() const;
    void hintSignal() const;

public slots:
    void updatePuzzleTiles(std::pair<unsigned, unsigned> tilePos, std::pair<unsigned, unsigned> emptyPos) const;
    void onGameFinish();
    void changeMovesCounter(unsigned moved) const;
    void setUndoButtonEnabled(bool) const;
    void setRedoButtonEnabled(bool) const;
    void updateTimer(QString newTime) const;
    void updateHintsCount(unsigned count) const;

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void hintPress() const;

private:
    void setupUiSizes();
    void setupConnections() const;
    void createButtons() const;

private:
    Ui::GameWindow* ui;
    PuzzleLogic*    m_puzzleLogic;
    QWidget*        m_mainWindow;
    HintDialog*     m_hintDialog;

};

#endif // GAMEWINDOW_H
