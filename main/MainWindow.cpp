#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_levelSelector(nullptr)
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

