#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QString>
#include <QFile>

#include <vector>

#include "JsonFile.h"
#include "gameLogic/PuzzleState.h"
#include "SaveData.h"

class SaveFile : public JsonFile
{
public:
    SaveFile(const QString& saveName);

    static bool saveExists(const QString& name);
    static bool isNameValid(const QString& name);

    void        saveGame(SaveData* saveData);
    SaveData*   loadGame();
private:

};

#endif // SAVEFILE_H
