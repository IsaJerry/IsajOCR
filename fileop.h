#ifndef FILEOP_H
#define FILEOP_H

#include <Includer.h>
#include "isajdata.h"

class FileOp
{
public:
    FileOp();
    FileOp(QWidget *parent);
    QString OpenFileDialog(QString model);
    QStringList ReadFile();
    void WriteTable(QTableWidget *table);
    void SavePath(QString path);

private:
    QWidget *parent;
    QString Path;
};

#endif // FILEOP_H
