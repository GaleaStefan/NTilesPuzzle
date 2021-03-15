#include "GameWindow.h"
#include "ui_GameWindow.h"

#define TILE_SIZE 64
#define TILE_SPACE 8
#define GROUP_BOX_OFFSET 16

GameWindow::GameWindow(const QString& saveName, int difficulty, QWidget* mainWindow) :
    ui(new Ui::GameWindow),
    m_puzzleLogic(new PuzzleLogic(this, difficulty + 2, saveName)),
    m_mainWindow(mainWindow)
{
    ui->setupUi(this);
    setupUiSizes();
    createButtons();

    ui->undoButton->setEnabled(false);
    ui->redoButton->setEnabled(false);

    connect(this, &GameWindow::tileClickSignal, m_puzzleLogic, &PuzzleLogic::onGameTilePress);
    connect(ui->saveCloseButton, &QPushButton::pressed, m_puzzleLogic, &PuzzleLogic::onSaveButtonPress);
    connect(ui->undoButton, &QPushButton::pressed, m_puzzleLogic, &PuzzleLogic::onUndoButtonPress);
    connect(ui->redoButton, &QPushButton::pressed, m_puzzleLogic, &PuzzleLogic::onRedoButtonPress);
}

GameWindow::GameWindow(const QString &saveName, QWidget *mainWindow) :
    ui(new Ui::GameWindow),
    m_mainWindow(mainWindow)
{
    ui->setupUi(this);
    m_puzzleLogic = new PuzzleLogic(this, saveName);
    m_puzzleLogic->gridSize();

    setupUiSizes();
    createButtons();

    connect(this, &GameWindow::tileClickSignal, m_puzzleLogic, &PuzzleLogic::onGameTilePress);
    connect(ui->saveCloseButton, &QPushButton::pressed, m_puzzleLogic, &PuzzleLogic::onSaveButtonPress);
    connect(ui->undoButton, &QPushButton::pressed, m_puzzleLogic, &PuzzleLogic::onUndoButtonPress);
    connect(ui->redoButton, &QPushButton::pressed, m_puzzleLogic, &PuzzleLogic::onRedoButtonPress);
}

GameWindow::~GameWindow()
{
    delete ui;
    delete m_puzzleLogic;
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
