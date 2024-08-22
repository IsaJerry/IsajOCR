#include "fileop.h"

FileOp::FileOp()
{

}

FileOp::FileOp(QWidget *parent)
{
    this->parent = parent;
    ClipBoard = QApplication::clipboard();
}

QString FileOp::OpenDialog(enum DialogModel model, QString keyWord)
{
    QString result;
    bool ok;
    switch (model) {
    case Open:
        if(parent != nullptr)
        {
            return QFileDialog::getOpenFileName(parent, "打开文件", "", "*.txt;; *.csv;; *.xlsx");
        }
        return QFileDialog::getOpenFileName(NULL, "打开文件", "", "*.txt;; *.csv;; *.xlsx");
        break;
    case Save:
        if(parent != nullptr)
        {
            return QFileDialog::getSaveFileName(parent, "保存文件", "", "*.txt;; *.csv;; *.xlsx");
        }
        return QFileDialog::getSaveFileName(NULL, "保存文件", "", "*.txt;; *.csv;; *.xlsx");
        break;
    case Text:
        if(parent != nullptr)
        {
            result = QInputDialog::getText(parent, "添加一次记录", "输入标题：", QLineEdit::Normal, NULL, &ok);
            if(ok)
            {
                return result;
            }
            return "null";
        }
        result = QInputDialog::getText(NULL, "添加一次记录", "输入标题：", QLineEdit::Normal, NULL, &ok);
            if(ok)
            {
                return result;
            }
            return "null";
        break;
    case KeyWord:
        if(parent != nullptr)
        {
            result = QInputDialog::getText(parent, "设置关键字", "学号关键字：", QLineEdit::Normal, keyWord, &ok);
            if(ok)
            {
                return result;
            }
            return "null";
        }
        result = QInputDialog::getText(NULL, "设置关键字", "学号关键字：", QLineEdit::Normal, keyWord, &ok);
            if(ok)
            {
                return result;
            }
            return "null";
        break;
    case Alter:
        if(parent != nullptr)
        {
            result = QInputDialog::getText(parent, "修改单元格内容", "修改为：", QLineEdit::Normal, keyWord, &ok);
            if(ok)
            {
                return result;
            }
            return "null";
        }
        result = QInputDialog::getText(NULL, "修改单元格内容", "修改为：", QLineEdit::Normal, keyWord, &ok);
            if(ok)
            {
                return result;
            }
            return "null";
        break;
    default:
        return "";
        break;
    }
}

QString FileOp::WhichTypeFile()
{
    if(Path.contains(".csv", Qt::CaseSensitive))
    {
        return CSVSPRIT;
    }
    else if(Path.contains(".xlsx", Qt::CaseSensitive))
    {
        return XLSX;
    }
    else
    {
        return TEXTSPRIT;
    }
}

QStringList FileOp::ReadFile()
{
    QStringList fileData;
    if(!ishasPath)
    {
        Path = OpenDialog(DialogModel::Open);
    }
    if(Path != "")
    {
        QFile File(Path);
        QTextStream in(&File);
        File.open(QIODevice::ReadOnly | QIODevice::Text);
        if(File.isOpen())
        {
            while(!in.atEnd())
            {
                fileData << in.readLine();
            }
        }
        else
        {
            fileData << "ERROR";
            QMessageBox::warning(parent, "错误", "文件打开失败");
        }
        File.close();
        if((new ISAJData())->ReadData(DEFAULT_LOAD) == ISAJ_TRUE)
        {
            SavePath(Path);
        }
    }
    else
    {
        fileData << "ERROR";
    }
    ishasPath = false;
    return fileData;
}

void FileOp::ReadFormExcel(QTableWidget *table)
{
    if(!ishasPath)
    {
        Path = OpenDialog(DialogModel::Open);
    }
    QAxObject *Excel = new QAxObject(parent);
    Excel->setControl("Excel.Application");
    Excel->dynamicCall("SetVisible (bool Visible)","false");
    Excel->setProperty("DisplayAlerts", false);
    QAxObject *works = Excel->querySubObject("WorkBooks");
    works->dynamicCall("Open (const QString&)", Path);
    QAxObject *workbook = Excel->querySubObject("ActiveWorkBook");
    QAxObject *sheet = workbook->querySubObject("Sheets(int)", 1);
    //QAxObject *sheet = sheets->querySubObject("Item(int)",1);
    QAxObject *Range;
    QString str;
    table->setRowCount(0);
    table->setColumnCount(0);
    for(int i=1;; i++)
    {
        table->setRowCount(table->rowCount()+1);
        for(int j=1;; j++)
        {
            Range = sheet->querySubObject("Cells(int,int)",i,j);
            if(Range != NULL)
            {
                table->setColumnCount(table->columnCount()+1);
                str = Range->dynamicCall("Value2()").toString();
                table->setItem(i-1, j-1, new QTableWidgetItem(str));
            }
            else
            {
                break;
            }
        }
        if(sheet->querySubObject("Cells(int,int)",i+1,1) == NULL)
        {
            break;
        }

    }
    workbook->dynamicCall("Close()");
    Excel->dynamicCall("Quit()");
    delete Excel;
    Excel = NULL;
}

void FileOp::setBottomBar(QStatusBar *bar)
{
    this->bar = bar;
}

void FileOp::WriteTable(QTableWidget *table, bool isSaveTo)
{
    QString sprit;
    if(isSaveTo)
    {

    }
    sprit = WhichTypeFile();
    if(Path != "")
    {
        QFile File(Path);
        QTextStream in(&File);
        //in.setEncoding(QStringConverter::Utf8);
        int row = table->rowCount();
        int column = table->columnCount();
        File.open(QIODevice::WriteOnly | QIODevice::Text);
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<column; j++)
            {
                if(table->item(i,j) != NULL)
                {
                    if(j<column-1)
                    {
                        in<<table->item(i,j)->text()<<sprit;
                    }
                    else
                    {
                        in<<table->item(i,j)->text();
                    }
                }
                else
                {
                    if(j<column-1)
                    {
                        in<<""<<sprit;
                    }
                    else
                    {
                        in<<"";
                    }
                }
            }
            in<<"\n";
        }
        File.close();
    }
    if((new ISAJData())->ReadData(DEFAULT_LOAD) == ISAJ_TRUE)
    {
        SavePath(Path);
    }
    //bar->addWidget(new QLabel("文件已打开" + Path));
}

void FileOp::WriteToExcel(QTableWidget *table, bool isSaveTo)
{
    if(isSaveTo)
    {

    }
    if(Path != "")
    {
        QAxObject *Excel = new QAxObject(parent);
        Excel->setControl("Excel.Application");
        Excel->dynamicCall("SetVisible (bool Visible)","false");
        Excel->setProperty("DisplayAlerts", false);
        QAxObject *works = Excel->querySubObject("WorkBooks");
        works->dynamicCall("Add");
        QAxObject *workbook = Excel->querySubObject("ActiveWorkBook");
        QAxObject *sheets = workbook->querySubObject("Sheets");
        QAxObject *sheet = sheets->querySubObject("Item(int)",1);
        for(int i=1; i<table->rowCount()+1; i++)
        {
            for(int j=1; j<table->columnCount()+1; j++)
            {
                QAxObject *Range = sheet->querySubObject("Cells(int,int)", i, j);
                Range->dynamicCall("SetValue(const QString &)", table->item(i-1, j-1)->text());
            }
        }
        workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(Path));
        workbook->dynamicCall("Close()");
        Excel->dynamicCall("Quit()");
        delete Excel;
        Excel = NULL;
    }
}

void FileOp::SavePath(QString path)
{
    ISAJData *data = new ISAJData();
    data->SaveData(FILE_PATH, path);
    //bar->addWidget(new QLabel("文件已保存"));
}

void FileOp::ReadFromPath(QString path)
{
    if(path != "null")
    {
        Path = path;
        ishasPath = true;
    }
}

bool FileOp::isPath()
{
    return ishasPath;
}

QString FileOp::RetnPath()
{
    return Path;
}

QString FileOp::Image2Base64(QImage image)
{
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return data.toBase64();
}

void FileOp::Copy(QString text)
{
    ClipBoard->setText(text);
}

QString FileOp::Paste()
{
    if(ClipBoard != NULL)
    {
        return ClipBoard->text();
    }
    else
    {
        return ISAJ_NULL;
    }
}

void FileOp::setPath(QString path)
{
    Path = path;
}
