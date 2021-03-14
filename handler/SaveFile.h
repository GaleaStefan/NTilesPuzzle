#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QString>
#include <QFile>

#include <vector>

#include "JsonFile.h"
#include "gameLogic/PuzzleState.h"

class SaveFile : public JsonFile
{
public:
    SaveFile();
    SaveFile(const QString& saveName);

    static bool saveExists(const QString& name);
    static bool isNameValid(const QString& name);

    void        saveGame(unsigned, unsigned, unsigned, unsigned, unsigned, std::vector<PuzzleState>);
private:

};

#endif // SAVEFILE_H
