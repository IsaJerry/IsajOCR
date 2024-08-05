#ifndef ISAJDATA_H
#define ISAJDATA_H

#include <Includer.h>

class ISAJData
{
public:
    ISAJData();
    ~ISAJData();
    void GetSettingFile();
    void SaveData(QString id, QString value);
    QString ReadData(QString id);

private:
    QSettings *ISAJSetting;
};

#endif // ISAJDATA_H
