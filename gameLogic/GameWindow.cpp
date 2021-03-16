#include "GameWindow.h"
#include "ui_GameWindow.h"
#include "main/MainWindow.h"

#define TILE_SIZE 64
#define TILE_SPACE 8
#define GROUP_BOX_OFFSET 16

GameWindow::GameWindow(const QString& saveName, int difficulty, QWidget* mainWindow) :
    ui(new Ui::GameWindow),
    m_puzzleLogic(new PuzzleLogic(this, difficulty + 2, saveName)),
    m_mainWindow(mainWindow),
    m_hintDialog(new HintDialog(this))
{
    ui->setupUi(this);
    setupUiSizes();
    createButtons();
    setupConnections();

    ui->undoButton->setEnabled(false);
    ui->redoButton->setEnabled(false);
}

GameWindow::GameWindow(const QString &saveName, QWidget *mainWindow) :
    ui(new Ui::GameWindow),
    m_mainWindow(mainWindow),
    m_hintDialog(new HintDialog(this))
{
    ui->setupUi(this);
    m_puzzleLogic = new PuzzleLogic(this, saveName);
    m_puzzleLogic->gridSize();

    setupUiSizes();
    createButtons();
    setupConnections();
}

GameWindow::~GameWindow()
{
    delete ui;
    delete m_puzzleLogic;
}

void GameWindow::enableHintButton() const
{
    ui->hintbutton->setEnabled(true);
}

void GameWindow::updatePuzzleTiles(std::pair<unsigned, unsigned> tilePos, std::pair<unsigned, unsigned> emptyPos) const
{
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->puzzleGroupBox->layout());

    QPushButton* pressed = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(tilePos.first, tilePos.second)->widget());
    pressed->disconnect();

    QPushButton* empty = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(emptyPos.first, emptyPos.second)->widget());
    empty->disconnect();

    gridLayout->addWidget(pressed, emptyPos.first, emptyPos.second);
    gridLayout->addWidget(empty, tilePos.first, tilePos.second);

    int emptyIndex = emptyPos.first * m_puzzleLogic->gridSize() + emptyPos.second;
    connect(pressed, &QPushButton::clicked,
            [this, emptyIndex]()
            {
                emit tileClickSignal(emptyIndex);
            }
    );

    int pressedIndex = tilePos.first * m_puzzleLogic->gridSize() + tilePos.second;
    connect(empty, &QPushButton::clicked,
            [this, pressedIndex]()
            {
                emit tileClickSignal(pressedIndex);
            }
    );
}

void GameWindow::setupUiSizes()
{
    int windowWidth = this->m_puzzleLogic->gridSize() * (TILE_SIZE + TILE_SPACE) + TILE_SPACE + 2 * GROUP_BOX_OFFSET;
    this->setFixedWidth(windowWidth);

    int groupBoxWidth = windowWidth - 2 * GROUP_BOX_OFFSET;
    ui->toolsGroupBox->setFixedWidth(groupBoxWidth);
    ui->puzzleGroupBox->setFixedSize(groupBoxWidth, groupBoxWidth);
    ui->infoGroupBox->setFixedWidth(groupBoxWidth);
    ui->saveCloseButton->setFixedWidth(groupBoxWidth);
}

void GameWindow::setupConnections() const
{
    MainWindow* castMain = qobject_cast<MainWindow*>(m_mainWindow);

    connect(this, &GameWindow::tileClickSignal, m_puzzleLogic, &PuzzleLogic::onGameTilePress);
    connect(ui->saveCloseButton, &QPushButton::pressed, this, &GameWindow::close);
    connect(ui->undoButton, &QPushButton::pressed, m_puzzleLogic, &PuzzleLogic::onUndoButtonPress);
    connect(ui->redoButton, &QPushButton::pressed, m_puzzleLogic, &PuzzleLogic::onRedoButtonPress);
    connect(ui->hintbutton, &QPushButton::pressed, this, &GameWindow::hintPress);
    connect(this, &GameWindow::windowCloseSignal, castMain, &MainWindow::onGameWindowClose);
    connect(this, &GameWindow::hintSignal, m_puzzleLogic, &PuzzleLogic::onHintButtonPress);
}

void GameWindow::createButtons() const
{
    unsigned gridSize = m_puzzleLogic->gridSize();

    for(unsigned index = 0; index < gridSize * gridSize; index++)
    {
        int tile = m_puzzleLogic->currentState().getTile(index);
        QString text = QString::number(tile);
        QPushButton* button = new QPushButton(ui->puzzleGroupBox);

        button->setFixedSize(TILE_SIZE, TILE_SIZE);
        button->setText((tile == 0) ? "" : text);
        button->setFlat(button->text() == "");
        button->setEnabled(!button->isFlat());

        int x = index / gridSize;
        int y = index % gridSize;
        QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->puzzleGroupBox->layout());

        gridLayout->addWidget(button, x, y);

        connect(button, &QPushButton::clicked,
                [this, index]()
                {
                    emit tileClickSignal(index);
                }
        );
    }
}

void GameWindow::onGameFinish()
{
    // BIG FINALE
}

void GameWindow::changeMovesCounter(unsigned moved) const
{
    ui->movesCount->setText(QString::number(moved));
}

void GameWindow::setUndoButtonEnabled(bool enabled) const
{
    ui->undoButton->setEnabled(enabled);
}

void GameWindow::setRedoButtonEnabled(bool enabled) const
{
    ui->redoButton->setEnabled(enabled);
}

void GameWindow::updateTimer(QString newTime) const
{
    ui->timeCount->setText(newTime);
}

void GameWindow::updateHintsCount(unsigned count) const
{
    ui->hintsCount->setText(QString::number(count));
}

void GameWindow::closeEvent(QCloseEvent *event)
{
    m_puzzleLogic->saveGame();

    emit windowCloseSignal();
}

void GameWindow::hintPress() const
{
    emit hintSignal();

    ui->hintbutton->setEnabled(false);
    m_hintDialog->getHint(m_puzzleLogic->currentState());
    m_hintDialog->show();
    m_hintDialog->exec();

    ui->hintbutton->setEnabled(true);
    m_hintDialog->hide();
}
