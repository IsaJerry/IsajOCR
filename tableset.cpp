#include "tableset.h"

TableSet::TableSet()
{

}

TableSet::TableSet(QTableWidget *table, QWidget *parent, QLineEdit *searchLine)
{
    this->Table = table;
    this->SearchLine = searchLine;
    file = new FileOp(parent);
}

void TableSet::DefaultLoad()
{

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

void TableSet::SetSearch()
{
    SearchTips = new QCompleter(SearchTipList, SearchLine);
    SearchTips->setCaseSensitivity(Qt::CaseInsensitive);
    SearchTips->setFilterMode(Qt::MatchContains);
    SearchLine->setCompleter(SearchTips);
}

void TableSet::SearchDisplay()
{
    QList<QTableWidgetItem *> searchlist = Table->findItems(SearchLine->text(), Qt::MatchContains);
    Table->scrollToItem(searchlist.at(0), QAbstractItemView::PositionAtCenter);
    Table->item(searchlist.at(0)->row(), searchlist.at(0)->column())->setSelected(true);
}
