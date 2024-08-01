#include "fileop.h"

FileOp::FileOp()
{

}

FileOp::FileOp(QWidget *parent)
{
    this->parent = parent;
}

QString FileOp::OpenFileDialog(QString model)
{
    if(model == "Open")
    {
        if(parent != nullptr)
        {
            return QFileDialog::getOpenFileName(parent, "打开文件", "", "*.txt");
        }
        return QFileDialog::getOpenFileName(NULL, "打开文件", "", ".txt");
    }
    else if(model == "Save")
    {
        if(parent != nullptr)
        {
            return QFileDialog::getSaveFileName(parent, "保存文件", "", ".txt");
        }
        return QFileDialog::getSaveFileName(NULL, "保存文件", "", ".txt");
    }
    else
    {
        QMessageBox::warning(NULL, "警告", "OpenFileDialog的model只能是Open和Save");
        return "";
    }
}

QStringList FileOp::ReadFile()
{
    QStringList fileData;
    Path = OpenFileDialog("Open");
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
    Path = OpenFileDialog("Save");
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
