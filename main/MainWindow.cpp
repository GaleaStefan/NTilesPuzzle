#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "handler/SaveFile.h"
#include "gameLogic/PuzzleState.h"
#include "loader/GameLoader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_levelSelector(nullptr)
    , m_gameWindow(nullptr)
{
    ui->setupUi(this);
    connect(ui->newButton, &QPushButton::pressed, this, &MainWindow::onNewBtnPress);
    connect(ui->loadButton, &QPushButton::pressed, this, &MainWindow::onLoadBtnPress);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_levelSelector;
    delete m_gameWindow;
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

void MainWindow::onLoadBtnPress()
{
    m_gameLoader = new GameLoader(this);
    m_gameLoader->show();
    m_gameLoader->exec();
}

void MainWindow::createNewGame(const QString &saveName, int difficulty)
{
    assert(m_gameWindow == nullptr);
    assert(m_levelSelector != nullptr);

    delete m_levelSelector;
    m_levelSelector = nullptr;

    this->hide();

    m_gameWindow = new GameWindow(saveName, difficulty, this);
    m_gameWindow->show();
}

void MainWindow::onSaveSelect(const QString &saveName)
{
    m_gameLoader->accept();
    delete m_gameLoader;

    this->hide();

    m_gameWindow = new GameWindow(saveName, this);
    m_gameWindow->show();
}
