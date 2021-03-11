#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "levels/LevelDialog.h"
#include "gameLogic/GameWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void createNewGame(const QString& saveName, int difficulty);

private slots:
    void onNewBtnPress();
    //void onLoadBtnPress();
    //void onAboutBtnPress();
    //void onHowBtnPress();

private:
    Ui::MainWindow *ui;
    LevelDialog *m_levelSelector;
    GameWindow *m_gameWindow;

};
#endif // MAINWINDOW_H
