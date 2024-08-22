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

void TableSet::setBottomBar(QStatusBar *bar)
{
    file->setBottomBar(bar);
}

void TableSet::DefaultLoad()
{
    if((new ISAJData())->ReadData(DEFAULT_LOAD) == ISAJ_TRUE)
    {
        DefaultOp->setChecked(true);
        file->ReadFromPath((new ISAJData())->ReadData(FILE_PATH));
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
    //if(file->WhichTypeFile() == XLSX)
    //{
    //    file->ReadFormExcel(Table);
    //}
    //else
    //{
        QStringList list = file->ReadFile();
        if(list.at(0) != "ERROR")
        {
            Table->setRowCount(list.length());
            Table->setColumnCount(GetTableLineData(list.at(0)).length());
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
    //}

}

void TableSet::NewTable()
{
    Table->clear();
    ISAJData *data = new ISAJData();
    QString text = data->ReadData(LoadRow);
    if(text != ISAJ_NULL)
    {
        Table->setRowCount(text.toInt());
    }
    else
    {
        Table->setRowCount(72);
    }
    text = data->ReadData(LoadColumn);
    if(text != ISAJ_NULL)
    {
        Table->setColumnCount(text.toInt());
    }
    else
    {
        Table->setColumnCount(2);
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
        (new ISAJData())->SaveData(DEFAULT_LOAD, ISAJ_TRUE);
        file->SavePath(file->RetnPath());
        isNew = false;
    }
    else
    {
        (new ISAJData())->SaveData(DEFAULT_LOAD, ISAJ_FALSE);
    }

}

void TableSet::CopyTable(int row, int column)
{
    QTableWidgetItem *item = Table->item(row, column);
    if(item != NULL)
    {
        file->Copy(item->text());
    }
}

void TableSet::PasteTable(int row, int column)
{
    QString text = file->Paste();
    if(text == ISAJ_NULL)
    {
        return;
    }
    Table->setItem(row, column, new QTableWidgetItem(text));
    isNew = true;
}

void TableSet::SaveTable()
{
    file->WriteTable(Table);
    isNew = false;
}

void TableSet::SaveTo()
{
    QString path = file->OpenDialog(file->Save);
    file->setPath(path);
    if(file->WhichTypeFile() == TEXTSPRIT)
    {
        file->WriteTable(Table, true);
    }
    else if(file->WhichTypeFile() == XLSX)
    {
        file->WriteToExcel(Table, true);
    }
    else
    {
    }
    isNew = false;
}

QStringList TableSet::GetTableLineData(QString linedata)
{
    QStringList tabletata;
    return tabletata = linedata.split(file->WhichTypeFile());
}

bool TableSet::RetnisNew()
{
    return isNew;
}

void TableSet::AddRecode(int column)
{
    QString title = file->OpenDialog(file->Text);
    if(title == "null")
    {
        return;
    }
    if(column == -1)
    {
        Table->insertColumn(Table->columnCount());
        Table->setItem(0, Table->columnCount()-1, new QTableWidgetItem(title));
    }
    else
    {
        Table->insertColumn(column);
        Table->setItem(0, column-1, new QTableWidgetItem(title));
    }
    isNew = true;
    addData(title);
}

void TableSet::AddRow(int row)
{
    if(row == -1)
    {
        Table->insertRow(Table->rowCount());
    }
    else
    {
        Table->insertRow(row);
    }
    isNew = true;
}

void TableSet::AddColumn(int column)
{
    if(column == -1)
    {
        Table->insertColumn(Table->columnCount());
    }
    else
    {
        Table->insertColumn(column);
    }
    isNew = true;
}

bool TableSet::RetnOcrColumn()
{
    return couldAdd;
}

void TableSet::AltItem(int row, int column)
{
    QString tips;
    if(Table->item(row, column) == NULL)
    {
        tips = "";
    }
    tips = Table->item(row, column)->text();
    QString text = file->OpenDialog(file->Alter, tips);
    if(text != "null")
    {
        Table->setItem(row, column, new QTableWidgetItem(text));
        removeData(tips);
        addData(text);
    }
}

void TableSet::SetOcrTarget(int column)
{
    ocrTarget = column;
    couldAdd = true;
}

void TableSet::SetFixed(int column)
{
    Header = Table->horizontalHeader();
    //int width = Table->columnWidth(column);
    Header->setSectionResizeMode(column, QHeaderView::Fixed);
    Header->resizeSection(column, 100);
}

void TableSet::DeleteItem(int row, int column)
{
    if(Table->item(row, column) != NULL)
    {
        removeData(Table->item(row, column)->text());
    }
    Table->setItem(row, column, new QTableWidgetItem(""));
    isNew = true;
}

void TableSet::DeleteLine(int row)
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
    isNew = true;
}

void TableSet::DeleteColumn(int row, int column)
{
    int ro = Table->rowCount();
    for(int i=0; i<ro; i++)
    {
        if(Table->item(i, column) != NULL)
        {
            removeData(Table->item(i, column)->text());
        }
    }
    Table->removeColumn(column);
    isNew = true;
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
    isNew = true;
}

void TableSet::setHandled(int row, int column, Handle handle)
{
    Table->setItem(row, column, Handled(handle));
    isNew = true;
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
    addData(item->text());
    return item;
}

void TableSet::addData(QString data)
{
    SearchTipList.append(data);
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

QStringList TableSet::RetnSearchTipList()
{
    return SearchTipList;
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
    QAction *copy = menu.addAction("复制");
    QAction *paste = menu.addAction("粘贴");
    QAction *Altitem = menu.addAction("修改");
    QAction *setocr = menu.addAction("设为Orc目标");
    QAction *setForizon = menu.addAction("冻结该列");
    QAction *addRowAt = menu.addAction("在此处添加一行");
    QAction *addColumnAt = menu.addAction("在此次添加一列");
    QAction *isHandle = menu.addAction("设为已提交");
    QAction *notHandle = menu.addAction("设为未提交");
    QAction *markAll = menu.addAction("标记所有未提交");
    QAction *delt = menu.addAction("删除");
    QAction *delLine = menu.addAction("删除该行");
    QAction *delCol = menu.addAction("删除该列");
    connect(copy, &QAction::triggered, Table, [=](){CopyTable(row, column);});
    connect(paste, &QAction::triggered, Table, [=](){PasteTable(row, column);});
    connect(Altitem, &QAction::triggered, Table, [=](){AltItem(row, column);});
    connect(setocr, &QAction::triggered, Table, [=](){SetOcrTarget(column);});
    connect(setForizon, &QAction::triggered, Table, [=](){SetFixed(column);});
    connect(addRowAt, &QAction::triggered, Table, [=](){AddRow(row);});
    connect(addColumnAt, &QAction::triggered, Table, [=](){AddColumn(column);});
    connect(isHandle, &QAction::triggered, Table, [=](){setHandled(row, column, isHandled);});
    connect(notHandle, &QAction::triggered, Table, [=](){setHandled(row, column, notHandled);});
    connect(markAll, &QAction::triggered, Table, [=](){MarkAllNotHandle(column);});
    connect(delt, &QAction::triggered, Table, [=](){DeleteItem(row, column);});
    connect(delLine, &QAction::triggered, Table, [=](){DeleteLine(row);});
    connect(delCol, &QAction::triggered, Table, [=](){DeleteColumn(row, column);});
    menu.exec(QCursor::pos());
}

