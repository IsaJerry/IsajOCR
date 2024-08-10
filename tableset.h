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

    enum Handle
    {
        isHandled = 1,
        notHandled = 0
    };

    void setBottomBar(QStatusBar *bar);
    void DefaultLoad();
    void SetTable();
    void NewTable();
    void DataOrRecode(int row, int column, QString text);
    void SaveTable();
    QStringList GetTableLineData(QString linedata);
    bool RetnisNew();

    void AddRecode(int column = -1);
    void AddRow(int row = -1);
    void AddColumn(int column = -1);

    bool RetnOcrColumn();
    void AltItem(int row, int column);
    void SetOcrTarget(int column);
    void SetFixed(int row, int column);
    void DeleteItem(int row, int column);
    void DeleteLine(int row);
    void DeleteColumn(int row, int column);

    void MarkAllNotHandle(int column);
    void setHandled(int row, int column, enum Handle handle);
    QTableWidgetItem *Handled(enum Handle handle);

    void addData(QString data);
    void removeData(QString data);

    void SetSearch();
    void Refeash();
    void SearchDisplay();
    QTableWidgetItem * RetnSearch();
    void OcrSearch(QString search);

    void SetDefault(bool checked);

    void Connections();

private:
    QList<QTableWidgetItem *> searchlist;
    QTableWidget *Table;
    QHeaderView *Header;
    QLineEdit *SearchLine;
    QStringList SearchTipList;
    QCompleter *SearchTips;
    QAction *DefaultOp;
    QAction *Save;
    FileOp *file;
    int ocrTarget;
    bool couldAdd = false;
    bool isNew = false;

protected:
    void ActionMenu(int row, int column);
};

#endif // TABLESET_H
