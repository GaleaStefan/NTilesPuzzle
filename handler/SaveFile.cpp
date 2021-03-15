#include "SaveFile.h"
#include <QException>

#define SAVE_PATH "./saves/"
#define SAVE_EXTENSION ".json"
#define SAVE_MIN_LEN 3

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

void SaveFile::saveGame(SaveData* saveData)
{
    QJsonValue gridValue = QJsonValue((int)saveData->m_grid);
    QJsonValue movesValue = QJsonValue((int)saveData->m_moves);
    QJsonValue hintsValue = QJsonValue((int)saveData->m_hints);
    QJsonValue timeValue = QJsonValue((int)saveData->m_time);
    QJsonValue currentValue = QJsonValue((int)saveData->m_state);


    QJsonArray statesArray;

    for(unsigned state = 0; state < saveData->m_history.size(); state++)
    {
        std::vector<unsigned> configuration = saveData->m_history[state].getState();
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

SaveData* SaveFile::loadGame()
{
    SaveData* saveData = new SaveData;

    saveData->m_grid = (unsigned)m_rootObject["grid"].toInt();
    saveData->m_moves = (unsigned)m_rootObject["moves"].toInt();
    saveData->m_hints = (unsigned)m_rootObject["hints"].toInt();
    saveData->m_time = (unsigned)m_rootObject["time"].toInt();
    saveData->m_state = (unsigned)m_rootObject["last_state"].toInt();

    QJsonArray statesArray = m_rootObject["states"].toArray();
    std::vector<PuzzleState> states;

    for(unsigned index = 0; index < statesArray.size(); index++)
    {
        QJsonArray state = statesArray[index].toArray();
        std::vector<unsigned> stateVector;

        for(unsigned tileIndex = 0; tileIndex < state.size(); tileIndex++)
        {
            stateVector.push_back((unsigned)state[tileIndex].toInt());
        }

        states.push_back(PuzzleState(saveData->m_grid, stateVector));
    }

    saveData->m_history = states;

    return saveData;
}
