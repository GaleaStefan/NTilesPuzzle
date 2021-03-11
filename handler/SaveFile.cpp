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
