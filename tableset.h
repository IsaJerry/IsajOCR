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

    void DefaultLoad();
    void SetTable();
    void DataOrRecode(int row, int column, QString text);
    void SaveTable();
    QStringList GetTableLineData(QString linedata);

    void AddRecode();
    void AddRow();
    void AddColumn();

    bool RetnOcrColumn();
    void SetOcrTarget(int column);
    void DeleteItem(int row, int column);
    void DeleteLine(int row, int column);
    void DeleteColumn(int row, int column);

    void MarkAllNotHandle(int column);
    void setHandled(int row, int column, enum Handle handle);
    QTableWidgetItem *Handled(enum Handle handle);

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
    QLineEdit *SearchLine;
    QStringList SearchTipList;
    QCompleter *SearchTips;
    QAction *DefaultOp;
    QAction *Save;
    FileOp *file;
    int ocrTarget;
    bool couldAdd = false;

protected:
    void ActionMenu(int row, int column);
};

#endif // TABLESET_H
