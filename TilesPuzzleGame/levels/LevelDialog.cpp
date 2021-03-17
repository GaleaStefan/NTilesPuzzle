#include "LevelDialog.h"
#include "ui_LevelDialog.h"

#include "../handler/SaveFile.h"
#include "../main/MainWindow.h"

LevelDialog::LevelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelDialog)
{
    ui->setupUi(this);

    m_currentLevel = ui->easyButton;
    m_currentLevel->setEnabled(false);

    m_btnLevels = {{ui->easyButton, 1},
                   {ui->mediumButton, 2},
                   {ui->hardButton, 3}};

    connect(ui->easyButton, &QPushButton::pressed, this, &LevelDialog::onLevelButtonPress);
    connect(ui->mediumButton, &QPushButton::pressed, this, &LevelDialog::onLevelButtonPress);
    connect(ui->hardButton, &QPushButton::pressed, this, &LevelDialog::onLevelButtonPress);
    connect(ui->cancelButton, &QPushButton::pressed, this, &LevelDialog::close);
    connect(ui->startButton, &QPushButton::pressed, this, &LevelDialog::onStartButtonPress);

    MainWindow* mainWindow = qobject_cast<MainWindow*>(parent);
    connect(this, &LevelDialog::onInputValidation, mainWindow, &MainWindow::createNewGame);
}

LevelDialog::~LevelDialog()
{
    delete ui;
}

void LevelDialog::onLevelButtonPress()
{
    m_currentLevel->setEnabled(true);

    m_currentLevel = qobject_cast<QPushButton*>(sender());
    m_currentLevel->setEnabled(false);
}

void LevelDialog::onStartButtonPress()
{
    QString saveName = ui->lineEdit->displayText();
    int chosenLevel = m_btnLevels[m_currentLevel];

    if(!SaveFile::isNameValid(saveName))
    {
        ui->errorsLabel->setText("Please insert a (valid) save name.\nAccepted characters:A-Z,a-z,0-9\n Min. name size: 3");
        return;
    }

    if(SaveFile::saveExists(saveName))
    {
        ui->errorsLabel->setText("Save already exists");
        return;
    }

    emit onInputValidation(saveName, chosenLevel);
}
