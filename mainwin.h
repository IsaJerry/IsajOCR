#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <IncludeItems.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWin; }
QT_END_NAMESPACE

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();

    void TableSetting();

    void SearchDataSet(QString text);
    void SearchSet();
    QString SearchCommit();
    void SimpleSearch();

    void SaveData();
    void WriteData(int row, int column, QFile *file);

    void AddRecode();
    void AddRow();
    void AddColumn();

    void CameraOpen();
    void CameraClose();

    void Connections();

signals:
    void SentTable(QTableWidget *table);

private:
    Ui::MainWin *ui;
    QStringList searchdata;
    QList<QTableWidgetItem *> searchList;
    TableSet *table;
    CameraSet *camera;

};
#endif // MAINWIN_H
