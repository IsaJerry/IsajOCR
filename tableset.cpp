#include "tableset.h"

TableSet::TableSet()
{
    Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

TableSet::TableSet(QTableWidget *table, QWidget *parent, QLineEdit *searchLine, QAction *defaultSave, QAction *save)
{
    Table = table;
    SearchLine = searchLine;
    DefaultOp = defaultSave;
    Save = save;
    file = new FileOp(parent);
    Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    DefaultLoad();
    Connections();
}

void TableSet::DefaultLoad()
{
    if((new ISAJData())->ReadData("DefaultLoad") == "true")
    {
        DefaultOp->setChecked(true);
        file->ReadFromPath((new ISAJData())->ReadData("filePath"));
        if(file->isPath())
        {
            SetTable();
        }
    }
    else
    {
        DefaultOp->setChecked(false);
    }
}

void TableSet::SetTable()
{
    QStringList list = file->ReadFile();
    Table->setRowCount(list.length());
    Table->setColumnCount(GetTableLineData(list.at(0)).length());
    if(list.at(0) != "ERROR")
    {
        for(int i=0; i<list.length(); i++)
        {
            QStringList datalist = GetTableLineData(list.at(i));
            SearchTipList << datalist;
            for(int j=0; j<datalist.length(); j++)
            {
                DataOrRecode(i, j, datalist.at(j));
            }
        }
        SetSearch();
        Save->setEnabled(true);
    }
}

void TableSet::DataOrRecode(int row, int column, QString text)
{
    if(text != "已提交" && text != "未提交")
    {
        Table->setItem(row, column, new QTableWidgetItem(text));
    }
    else if(text == "已提交" && text != "未提交")
    {
        Table->setItem(row, column, Handled(isHandled));
    }
    else
    {
        Table->setItem(row, column, Handled(notHandled));
    }
}

void TableSet::SetDefault(bool checked)
{
    if(checked)
    {
        (new ISAJData())->SaveData("DefaultLoad", "true");
    }
    else
    {
        (new ISAJData())->SaveData("DefaultLoad", "false");
    }

}

void TableSet::SaveTable()
{
    file->WriteTable(Table);
}

QStringList TableSet::GetTableLineData(QString linedata)
{
    QStringList tabletata;
    return tabletata = linedata.split("\t");
}

void TableSet::AddRecode()
{
    //couldAdd = false;
    QString title = file->OpenDialog(file->Text);
    if(title == "null")
    {
        return;
    }
    //couldAdd = true;
    Table->setColumnCount(Table->columnCount()+1);
    Table->setItem(0, Table->columnCount()-1, new QTableWidgetItem(title));
}

void TableSet::AddRow()
{
    Table->setRowCount(Table->rowCount()+1);
}

void TableSet::AddColumn()
{
    Table->setColumnCount(Table->columnCount()+1);
}

bool TableSet::RetnOcrColumn()
{
    return couldAdd;
}

void TableSet::SetOcrTarget(int column)
{
    ocrTarget = column;
    couldAdd = true;
}

void TableSet::DeleteItem(int row, int column)
{
    QString data = Table->item(row, column)->text();
    Table->setItem(row, column, new QTableWidgetItem(""));
    removeData(data);
}

void TableSet::DeleteLine(int row, int column)
{
    int col = Table->columnCount();
    for(int i=0; i<col; i++)
    {
        if(Table->item(row, i) != NULL)
        {
            removeData(Table->item(row, i)->text());
        }
    }
    Table->removeRow(row);
}

void TableSet::DeleteColumn(int row, int column)
{
    int ro = Table->rowCount();
    for(int i=0; i<ro; i++)
    {
        if(Table->item(row, i) != NULL)
        {
            removeData(Table->item(i, column)->text());
        }
    }
    Table->removeColumn(column);
}

void TableSet::MarkAllNotHandle(int column)
{
    int row = Table->rowCount();
    for(int i=0; i<row; i++)
    {
        if(Table->item(i, column) == NULL)
        {
            setHandled(i, column, notHandled);
        }
    }
}

void TableSet::setHandled(int row, int column, Handle handle)
{
    Table->setItem(row, column, Handled(handle));
}

QTableWidgetItem *TableSet::Handled(Handle handle)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    switch (handle)
    {
    case isHandled:
        item->setText("已提交");
        item->setForeground(QBrush(Qt::white));
        item->setBackground(QBrush(Qt::blue));
        break;
    case notHandled:
        item->setText("未提交");
        item->setBackground(QBrush(Qt::red));
        break;
    default:
        break;
    }
    return item;
}

void TableSet::removeData(QString data)
{
    SearchTipList.removeOne(data);
}

void TableSet::SetSearch()
{
    SearchTips = new QCompleter(SearchTipList, SearchLine);
    SearchTips->setCaseSensitivity(Qt::CaseInsensitive);
    SearchTips->setFilterMode(Qt::MatchContains);
    SearchLine->setCompleter(SearchTips);
}

void TableSet::Refeash()
{

}

void TableSet::SearchDisplay()
{
    if(SearchLine->text() != "")
    {
        searchlist = Table->findItems(SearchLine->text(), Qt::MatchContains);
        Table->scrollToItem(searchlist.at(0), QAbstractItemView::PositionAtCenter);
        Table->item(searchlist.at(0)->row(), searchlist.at(0)->column())->setSelected(true);
    }
}

QTableWidgetItem *TableSet::RetnSearch()
{
    return searchlist.at(0);
}

void TableSet::OcrSearch(QString search)
{
    SearchLine->setText(search);
    SearchDisplay();
    Table->setItem(searchlist.at(0)->row(), ocrTarget, Handled(isHandled));
}

void TableSet::Connections()
{
    connect(this->Table, &QTableWidget::cellDoubleClicked, this, &TableSet::ActionMenu);
}

void TableSet::ActionMenu(int row, int column)
{
    QMenu menu;
    QAction *setocr = menu.addAction("设为Orc目标");
    QAction *isHandle = menu.addAction("设为已提交");
    QAction *notHandle = menu.addAction("设为未提交");
    QAction *markAll = menu.addAction("标记所有未提交");
    QAction *delt = menu.addAction("删除");
    QAction *delLine = menu.addAction("删除该行");
    QAction *delCol = menu.addAction("删除该列");
    connect(setocr, &QAction::triggered, Table, [=](){
        SetOcrTarget(column);
    });
    connect(isHandle, &QAction::triggered, Table, [=](){
        setHandled(row, column, isHandled);
    });
    connect(notHandle, &QAction::triggered, Table, [=](){
        setHandled(row, column, notHandled);
    });
    connect(markAll, &QAction::triggered, Table, [=](){
        MarkAllNotHandle(column);
    });
    connect(delt, &QAction::triggered, Table, [=](){
        DeleteItem(row, column);
    });
    connect(delLine, &QAction::triggered, Table, [=](){
        DeleteLine(row, column);
    });
    connect(delCol, &QAction::triggered, Table, [=](){
        DeleteColumn(row, column);
    });
    menu.exec(QCursor::pos());
}

