#include "JsonFile.h"
#include <QDir>

JsonFile::JsonFile() :
    m_file(nullptr)
{
}

JsonFile::JsonFile(const QString& path, const QString& name) :
    m_file(nullptr)
{
    if(!JsonFile::fileExists(path, name))
    {
        JsonFile::createFile(path, name);
    }

    openFile(path, name);
}

JsonFile::~JsonFile()
{
    if(m_file != nullptr)
    {
        delete  m_file;
    }
}

bool JsonFile::fileExists(const QString& path, const QString& name)
{
    return QFile::exists(path + name);
}

void JsonFile::createFile(const QString &path, const QString &name)
{
    QDir dir(path);

    if(!dir.exists())
    {
        dir.mkpath(".");
    }

    QFile* file = new QFile(path + name);
    file->open(QIODevice::ReadWrite);
    file->close();
    delete file;
}

void JsonFile::openFile(const QString& path, const QString& name)
{
    m_file = new QFile(path + name);
    m_file->open(QIODevice::ReadWrite);

    m_jsonDoc = QJsonDocument::fromJson(m_file->readAll());
    m_rootObject = m_jsonDoc.object();
}

void JsonFile::saveFile()
{
    m_file->seek(0);
    m_file->write(m_jsonDoc.toJson());
    m_file->close();
}

QJsonValue JsonFile::getValue(const QString &key) const
{
    return m_rootObject.value(key);
}
