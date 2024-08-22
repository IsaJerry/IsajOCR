#ifndef FILEOP_H
#define FILEOP_H

#include <Includer.h>
#include <ActiveQt/QAxObject>
#include "isajdata.h"

#define TEXTSPRIT "\t"
#define CSVSPRIT ","
#define XLSX "xlsx"


class FileOp
{
public:
    FileOp();
    FileOp(QWidget *parent);
    QStringList ReadFile();
    void ReadFormExcel(QTableWidget *table);
    void setBottomBar(QStatusBar *bar);
    void WriteTable(QTableWidget *table, bool isSaveTo = false);
    void WriteToExcel(QTableWidget *table, bool isSaveTo = false);
    void SavePath(QString path);
    void ReadFromPath(QString path);
    bool isPath();
    QString RetnPath();
    QString Image2Base64(QImage image);
    void Copy(QString text);
    QString Paste();

    enum DialogModel
    {
        Open = 1,
        Save = 2,
        Text = 3,
        KeyWord = 4,
        Alter = 5
    };

    QString OpenDialog(enum DialogModel model, QString keyWord = "not set");
    QString WhichTypeFile();

private:
    QWidget *parent;
    QStatusBar *bar;
    QString Path;
    QClipboard *ClipBoard;
    bool ishasPath = false;
};



#endif // FILEOP_H
