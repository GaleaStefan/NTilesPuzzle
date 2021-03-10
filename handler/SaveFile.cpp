#include "SaveFile.h"
#include <QFile>
#include <qjsonobject.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QException>

#define SAVE_PATH "saves/"
#define SAVE_EXTENSION ".json"
#define SAVE_MIN_LEN 3

SaveFile::SaveFile()
{

}

SaveFile::SaveFile(const QString &newSaveName)
{
    QJsonObject informations;
    informations.insert("difficulty", 0);
    informations.insert("time", 0);
    informations.insert("moves", 0);

    QJsonArray state {0, 0, 0, 0, 0};

    informations["state"] = state;

    QJsonDocument document(informations);
    qInfo() << document.toJson();
}

bool SaveFile::saveExists(const QString &name)
{
    QFile saveFile(SAVE_PATH + name + SAVE_EXTENSION);

    return saveFile.exists();
}

bool SaveFile::isNameValid(const QString &name)
{
    if(name.length() < SAVE_MIN_LEN)
    {
        return false;
    }

    for(int index = 0; index < name.size(); index++)
    {
        if(!name[index].isLetterOrNumber())
        {
            return false;
        }
    }

    return true;
}
