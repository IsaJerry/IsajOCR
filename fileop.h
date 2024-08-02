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
    void WriteTable(QTableWidget *table);
    void SavePath(QString path);
    void ReadFromPath(QString path);
    bool isPath();

    enum DialogModel
    {
        Open = 1,
        Save = 2,
        Text = 3
    };

    QString OpenDialog(enum DialogModel model);

private:
    QWidget *parent;
    QString Path;
    bool ishasPath = false;
};



#endif // FILEOP_H
