#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QString>
#include <QFile>

#include "JsonFile.h"

class SaveFile : public JsonFile
{
public:
    SaveFile();
    SaveFile(const QString& saveName);

    static bool saveExists(const QString& name);
    static bool isNameValid(const QString& name);

private:

};

#endif // SAVEFILE_H
