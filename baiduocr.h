#ifndef BAIDUOCR_H
#define BAIDUOCR_H

#include "ocrsystem.h"
#include <QWidget>

namespace Ui {
class BaiduOCR;
}

class BaiduOCR : public QWidget
{
    Q_OBJECT

public:
    explicit BaiduOCR(QWidget *parent = nullptr);
    ~BaiduOCR();

    void SetWidget();
    void SetSetting();
    void OpenWidget();
    void Connection();

private:
    Ui::BaiduOCR *ui;
    OCRSystem *system;
};

#endif // BAIDUOCR_H
