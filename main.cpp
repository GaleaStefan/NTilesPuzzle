#include "main/MainWindow.h"
#include <QApplication>

//TEST
#include "gameSolver/PuzzleSolver.h"
#include "gameLogic/PuzzleState.h"

int main(int argc, char *argv[])
{
    PuzzleState testState = PuzzleState::generateRandomState(3);
    PuzzleSolver solver(testState);

    solver.solvePuzzle();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
