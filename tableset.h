#ifndef TABLESET_H
#define TABLESET_H

#include "qmainwindow.h"
#include <Includer.h>
#include <fileop.h>

class TableSet : public QMainWindow
{
public:
    TableSet();
    TableSet(QTableWidget *table, QWidget *parent, QLineEdit *searchLine, QAction *defaultSave, QAction *save);

    void DefaultLoad();
    void SetTable();
    void SaveTable();
    QStringList GetTableLineData(QString linedata);

    void AddRecode();
    void AddRow();
    void AddColumn();

    void SetSearch();
    void SearchDisplay();

    void SetDefault(bool checked);

private:
    QTableWidget *Table;
    QLineEdit *SearchLine;
    QStringList SearchTipList;
    QCompleter *SearchTips;
    QAction *DefaultOp;
    QAction *Save;
    FileOp *file;
};

#endif // TABLESET_H
