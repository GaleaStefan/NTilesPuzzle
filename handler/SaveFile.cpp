#include "SaveFile.h"
#include <QException>

#define SAVE_PATH "./saves/"
#define SAVE_EXTENSION ".json"
#define SAVE_MIN_LEN 3

SaveFile::SaveFile()
{

}

SaveFile::SaveFile(const QString &saveName) :
    JsonFile(SAVE_PATH, saveName + SAVE_EXTENSION)
{
}

bool SaveFile::saveExists(const QString &name)
{
    return JsonFile::fileExists(SAVE_PATH, name + SAVE_EXTENSION);
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

void SaveFile::saveGame(unsigned grid, unsigned moves, unsigned hints, unsigned time, unsigned currentState, std::vector<PuzzleState> states)
{
    QJsonValue gridValue = QJsonValue((int)grid);
    QJsonValue movesValue = QJsonValue((int)moves);
    QJsonValue hintsValue = QJsonValue((int)hints);
    QJsonValue timeValue = QJsonValue((int)time);
    QJsonValue currentValue = QJsonValue((int)currentState);


    QJsonArray statesArray;

    for(unsigned state = 0; state < states.size(); state++)
    {
        std::vector<unsigned> configuration = states[state].getState();
        QJsonArray configArray;

        for(unsigned index = 0; index < configuration.size(); index++)
        {
            configArray.push_back(QJsonValue((int)configuration[index]));
        }

        statesArray.push_back(configArray);
    }

    m_rootObject["grid"] = gridValue;
    m_rootObject["moves"] = movesValue;
    m_rootObject["hints"] = hintsValue;
    m_rootObject["time"] = timeValue;
    m_rootObject["last_state"] = currentValue;
    m_rootObject["states"] = statesArray;

    m_jsonDoc = QJsonDocument(m_rootObject);

    saveFile();
}
