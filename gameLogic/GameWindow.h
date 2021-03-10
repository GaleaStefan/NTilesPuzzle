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
    explicit GameWindow(int difficulty, QWidget *parent = nullptr);
    ~GameWindow();

    void updatePuzzleTiles(std::pair<unsigned, unsigned> tilePos, std::pair<unsigned, unsigned> emptyPos) const;

private:
    Ui::GameWindow *ui;
    PuzzleLogic* m_puzzleLogic;

private:
    void setupUiSizes();
    void createButtons() const;

private slots:
    void onTileButtonClick(unsigned index) const;
};

#endif // GAMEWINDOW_H
