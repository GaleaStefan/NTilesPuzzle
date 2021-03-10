#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QString>
#include <QFile>


class SaveFile
{
public:
    SaveFile();
    SaveFile(const QString& newSaveName);

    static bool saveExists(const QString& name);
    static bool isNameValid(const QString& name);
private:
    QFile m_file;
};

#endif // SAVEFILE_H
