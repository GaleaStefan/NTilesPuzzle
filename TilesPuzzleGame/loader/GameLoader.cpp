#include "GameLoader.h"
#include "ui_GameLoader.h"

#include "main/MainWindow.h"

#include <QListWidgetItem>
#include <QList>
#include <QDir>

GameLoader::GameLoader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameLoader)
{
    ui->setupUi(this);

    MainWindow* mainWindow = qobject_cast<MainWindow*>(parent);
    connect(this, &GameLoader::saveChosenSignal, mainWindow, &MainWindow::onSaveSelect);
    connect(ui->selectSaveButton, &QPushButton::pressed, this, &GameLoader::onSelectButtonPress);

    loadSaveFiles();
}

GameLoader::~GameLoader()
{
    delete ui;
}

void GameLoader::onSelectButtonPress()
{
    QList<QListWidgetItem*> selectedSaves = ui->saveFiles->selectedItems();

    if(selectedSaves.size() != 1)
    {
        return;
    }

    emit saveChosenSignal(selectedSaves[0]->text());
}

void GameLoader::loadSaveFiles() const
{
    QDir saveDir("./saves");
    saveDir.setNameFilters({"*.json"});

    QStringList filesList = saveDir.entryList();
    QStringList::const_iterator filesIterator;

    for (filesIterator = filesList.constBegin(); filesIterator < filesList.constEnd(); filesIterator++)
    {
        QString name = *filesIterator;
        name.remove(".json");

        ui->saveFiles->addItem(name);
    }
}
