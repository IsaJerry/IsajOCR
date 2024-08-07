#include "fileop.h"

FileOp::FileOp()
{

}

FileOp::FileOp(QWidget *parent)
{
    this->parent = parent;
}

QString FileOp::OpenDialog(enum DialogModel model, QString keyWord)
{
    QString result;
    bool ok;
    switch (model) {
    case Open:
        if(parent != nullptr)
        {
            return QFileDialog::getOpenFileName(parent, "打开文件", "", "*.txt");
        }
        return QFileDialog::getOpenFileName(NULL, "打开文件", "", "*.txt");
        break;
    case Save:
        if(parent != nullptr)
        {
            return QFileDialog::getSaveFileName(parent, "保存文件", "", "*.txt");
        }
        return QFileDialog::getSaveFileName(NULL, "保存文件", "", "*.txt");
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
            result = QInputDialog::getText(parent, "设置关键字", "输入标题：", QLineEdit::Normal, keyWord, &ok);
            if(ok)
            {
                qDebug()<<"yes";
                return result;
            }
            return "null";
        }
        result = QInputDialog::getText(NULL, "设置关键字", "输入标题：", QLineEdit::Normal, keyWord, &ok);
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
    }
    else
    {
        fileData << "ERROR";
    }
    return fileData;
}

void FileOp::WriteTable(QTableWidget *table)
{
    if((new ISAJData())->ReadData("DefaultLoad") == "true")
    {
        SavePath(Path);
    }
    Path = OpenDialog(DialogModel::Save);
    if(Path != "")
    {
        QFile File(Path);
        QTextStream in(&File);
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
                        in<<table->item(i,j)->text()<<"\t";
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
                        in<<""<<"\t";
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
}

void FileOp::SavePath(QString path)
{
    ISAJData *data = new ISAJData();
    data->SaveData("filePath", path);
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

QString FileOp::Image2Base64(QImage image)
{
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return data.toBase64();
}
