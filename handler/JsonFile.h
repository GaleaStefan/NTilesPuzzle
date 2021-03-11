#ifndef JSONFILE_H
#define JSONFILE_H

#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

class JsonFile
{
public:
    JsonFile();
    JsonFile(const QString& path, const QString& name);
    ~JsonFile();

    static bool fileExists(const QString& path, const QString& name);
    static void createFile(const QString& path, const QString& name);
    void        openFile(const QString& path, const QString& name);

    QJsonValue  getValue(const QString& key) const;

    template    <class ValueType>
    void        setValue(const QString& key, ValueType value);

protected:
    QFile*          m_file;
    QJsonDocument   m_jsonDoc;
    QJsonObject     m_rootObject;
};

template <class ValueType>
void JsonFile::setValue(const QString& key, ValueType value)
{
    m_rootObject[key] = value;
}

#endif // JSONFILE_H
