#ifndef BAIDUOCR_H
#define BAIDUOCR_H

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
    void Connection();

private:
    Ui::BaiduOCR *ui;
};

#endif // BAIDUOCR_H
