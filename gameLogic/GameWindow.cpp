#include "GameWindow.h"
#include "ui_GameWindow.h"

#define TILE_SIZE 64
#define TILE_SPACE 8
#define GROUP_BOX_OFFSET 16

GameWindow::GameWindow(int difficulty, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    m_puzzleLogic(new PuzzleLogic(this, difficulty + 2))
{
    ui->setupUi(this);
    setupUiSizes();
    createButtons();
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
                onTileButtonClick(emptyIndex);
            }
    );

    int pressedIndex = tilePos.first * m_puzzleLogic->gridSize() + tilePos.second;
    connect(empty, &QPushButton::clicked,
            [this, pressedIndex]()
            {
                onTileButtonClick(pressedIndex);
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
        QPushButton* button = new QPushButton(ui->puzzleGroupBox);
        button->setFixedSize(TILE_SIZE, TILE_SIZE);

        int tile = m_puzzleLogic->currentState().getTile(index);
        QString text = QString::number(tile);
        button->setText((tile == 0) ? "" : text);
        button->setFlat(button->text() == text);

        QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->puzzleGroupBox->layout());

        int x = index / gridSize;
        int y = index % gridSize;
        gridLayout->addWidget(button, x, y);

        connect(button, &QPushButton::clicked,
                [this, index]()
                {
                    onTileButtonClick(index);
                }
        );
    }
}

void GameWindow::onTileButtonClick(unsigned buttonIndex) const
{
    m_puzzleLogic->handleTilePress(buttonIndex);
}
