#ifndef MAINWIN_H
#define MAINWIN_H

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

    void SetWidget();

    void Connections();

private:
    Ui::MainWin *ui;

protected:
    TableSet *table;
    CameraSet *camera;
    BaiduOCR *baidu;

};
#endif // MAINWIN_H
