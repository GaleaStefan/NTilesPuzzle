#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "levels/LevelDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LevelDialog *m_levelSelector;
private slots:
    void onNewBtnPress();
    //void onLoadBtnPress();
    //void onAboutBtnPress();
    //void onHowBtnPress();
};
#endif // MAINWINDOW_H
