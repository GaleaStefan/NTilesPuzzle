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
    explicit GameWindow(const QString& saveName, int difficulty, QWidget *parent = nullptr);
    ~GameWindow();

signals:
    void tileClickSignal(int index) const;

public slots:
    void updatePuzzleTiles(std::pair<unsigned, unsigned> tilePos, std::pair<unsigned, unsigned> emptyPos, int moves, bool finished) const;
    void updateMoves(unsigned moves) const;
    void onGameFinish();

private:
    void setupUiSizes();
    void createButtons() const;

private slots:
    void onTileButtonClick(unsigned index) const;

private:
    Ui::GameWindow* ui;
    PuzzleLogic*    m_puzzleLogic;
};

#endif // GAMEWINDOW_H
