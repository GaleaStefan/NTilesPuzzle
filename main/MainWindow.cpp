#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "handler/SaveFile.h"
#include "gameLogic/PuzzleState.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_levelSelector(nullptr)
    , m_gameWindow(nullptr)
{
    ui->setupUi(this);

    connect(ui->newButton, &QPushButton::pressed, this, &MainWindow::onNewBtnPress);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewBtnPress()
{
    assert(m_levelSelector == nullptr);

    m_levelSelector = new LevelDialog(this);
    m_levelSelector->show();
    m_levelSelector->exec();

    delete m_levelSelector;
    m_levelSelector = nullptr;
}

void MainWindow::startNewGame(const QString &saveFileName, int difficulty)
{
    assert(m_gameWindow == nullptr);
    assert(m_levelSelector != nullptr);

    delete m_levelSelector;
    m_levelSelector = nullptr;

    this->hide();

    m_gameWindow = new GameWindow(difficulty);
    m_gameWindow->show();
}

