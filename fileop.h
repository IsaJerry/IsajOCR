#ifndef FILEOP_H
#define FILEOP_H

#include <Includer.h>
#include "isajdata.h"

class FileOp
{
public:
    FileOp();
    FileOp(QWidget *parent);
    QStringList ReadFile();
    void setBottomBar(QStatusBar *bar);
    void WriteTable(QTableWidget *table);
    void SavePath(QString path);
    void ReadFromPath(QString path);
    bool isPath();
    QString RetnPath();
    QString Image2Base64(QImage image);

    enum DialogModel
    {
        Open = 1,
        Save = 2,
        Text = 3,
        KeyWord = 4,
        Alter = 5
    };

    QString OpenDialog(enum DialogModel model, QString keyWord = "not set");

private:
    QWidget *parent;
    QStatusBar *bar;
    QString Path;
    bool ishasPath = false;
};



#endif // FILEOP_H