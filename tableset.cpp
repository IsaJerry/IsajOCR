#include "tableset.h"

TableSet::TableSet()
{

}

TableSet::TableSet(QTableWidget *table, QWidget *parent, QLineEdit *searchLine, QAction *defaultSave, QAction *save)
{
    Table = table;
    SearchLine = searchLine;
    DefaultOp = defaultSave;
    Save = save;
    file = new FileOp(parent);
    DefaultLoad();
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
                Table->setItem(i, j, new QTableWidgetItem(datalist.at(j)));
            }
        }
        SetSearch();
        Save->setEnabled(true);
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
    QString title = file->OpenDialog(file->Text);
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

void TableSet::SetSearch()
{
    SearchTips = new QCompleter(SearchTipList, SearchLine);
    SearchTips->setCaseSensitivity(Qt::CaseInsensitive);
    SearchTips->setFilterMode(Qt::MatchContains);
    SearchLine->setCompleter(SearchTips);
}

void TableSet::SearchDisplay()
{
    if(SearchLine->text() != "")
    {
        QList<QTableWidgetItem *> searchlist = Table->findItems(SearchLine->text(), Qt::MatchContains);
        Table->scrollToItem(searchlist.at(0), QAbstractItemView::PositionAtCenter);
        Table->item(searchlist.at(0)->row(), searchlist.at(0)->column())->setSelected(true);
    }
}
