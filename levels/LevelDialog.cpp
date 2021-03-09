#include "LevelDialog.h"
#include "ui_LevelDialog.h"

LevelDialog::LevelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelDialog),
    m_currentLevel(nullptr)
{
    ui->setupUi(this);

    m_btnLevels = {{ui->easyButton, 1},
                   {ui->mediumButton, 2},
                   {ui->hardButton, 3}};

    connect(ui->easyButton, &QPushButton::pressed, this, &LevelDialog::onLevelButtonPress);
    connect(ui->mediumButton, &QPushButton::pressed, this, &LevelDialog::onLevelButtonPress);
    connect(ui->hardButton, &QPushButton::pressed, this, &LevelDialog::onLevelButtonPress);
    connect(ui->cancelButton, &QPushButton::pressed, this, &LevelDialog::close);
    connect(ui->startButton, &QPushButton::pressed, this, &LevelDialog::onStartButtonPress);
}

LevelDialog::~LevelDialog()
{
    delete ui;
}

void LevelDialog::onLevelButtonPress()
{
    if(m_currentLevel != nullptr)
    {
        m_currentLevel->setEnabled(true);
    }

    m_currentLevel = qobject_cast<QPushButton*>(sender());
    m_currentLevel->setEnabled(false);
}

void LevelDialog::onStartButtonPress()
{
    if(m_currentLevel == nullptr)
    {
        ui->errorsLabel->setText("Please choose a difficulty");
        return;
    }

    QString saveName = ui->lineEdit->displayText();
    int chosenLevel = m_btnLevels[m_currentLevel];

    if(!isSaveNameValid(saveName))
    {
        ui->errorsLabel->setText("Please insert a (valid) save name");
        return;
    }

    qInfo() << saveName << chosenLevel;
}

bool LevelDialog::isSaveNameValid(const QString& saveName)
{
    return true;
}
