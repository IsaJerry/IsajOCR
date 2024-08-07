#ifndef TABLESET_H
#define TABLESET_H

#include <Includer.h>
#include <fileop.h>
#include <QMenu>

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

    void DeleteItem(int row, int column);
    void DeleteLine(int row, int column);

    void removeData(QString data);

    void SetSearch();
    void Refeash();
    void SearchDisplay();
    void OcrSearch(QString search);

    void SetDefault(bool checked);

    void Connections();

private:
    QTableWidget *Table;
    QLineEdit *SearchLine;
    QStringList SearchTipList;
    QCompleter *SearchTips;
    QAction *DefaultOp;
    QAction *Save;
    FileOp *file;

protected:
    void ActionMenu(int row, int column);
};

#endif // TABLESET_H
