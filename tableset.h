#ifndef TABLESET_H
#define TABLESET_H

#include <Includer.h>
#include <fileop.h>

class TableSet
{
public:
    TableSet();
    TableSet(QTableWidget *table, QWidget *parent, QLineEdit *searchLine);

    void SetTable();
    void SaveTable();
    QStringList GetTableLineData(QString linedata);

    void SetSearch();
    void SearchDisplay();

private:
    QTableWidget *Table;
    QLineEdit *SearchLine;
    QStringList SearchTipList;
    QCompleter *SearchTips;
    FileOp *file;
};

#endif // TABLESET_H
