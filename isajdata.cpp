#include "isajdata.h"

ISAJData::ISAJData()
{
    GetSettingFile();
}

ISAJData::~ISAJData()
{
    delete ISAJSetting;
}

void ISAJData::GetSettingFile()
{
    QString path = QCoreApplication::applicationDirPath() + "/ISAJ.ini";
    if(!QFile::exists(path))
    {
        QFile file(path);
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    ISAJSetting = new QSettings(path, QSettings::IniFormat);

}

void ISAJData::SaveData(QString id, QString value)
{
    if(ISAJSetting->contains(id))
    {
        if(ISAJSetting->value(id) != value)
        {
            ISAJSetting->setValue(id, value);
        }
    }
    else
    {
        ISAJSetting->setValue(id, value);
    }
}

QString ISAJData::ReadData(QString id)
{
    if(ISAJSetting->contains(id))
    {
        return ISAJSetting->value(id).toString();
    }
    else
    {
        return "null";
    }
}
