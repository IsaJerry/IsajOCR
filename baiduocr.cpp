#include "baiduocr.h"
#include "ui_baiduocr.h"

BaiduOCR::BaiduOCR(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaiduOCR)
{
    ui->setupUi(this);
}

BaiduOCR::~BaiduOCR()
{
    delete ui;
}
