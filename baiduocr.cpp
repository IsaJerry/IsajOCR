#include "baiduocr.h"
#include "ui_baiduocr.h"

BaiduOCR::BaiduOCR(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaiduOCR)
{
    ui->setupUi(this);
    system = new OCRSystem();

    Connection();
}

BaiduOCR::~BaiduOCR()
{
    delete ui;
}

void BaiduOCR::SetWidget()
{
    this->setFixedSize(330, 210);
}

void BaiduOCR::SetSetting()
{
    QString reasult = system->getAccessToken(ui->apiKeyLine->text(), ui->SecretKeyLine->text());
    if(reasult != "success")
    {
        QMessageBox::warning(this, "ERROR", reasult);
        return;
    }
    QMessageBox::information(this, "消息", "获取成功");
}

void BaiduOCR::OpenWidget()
{
    ISAJData *data = new ISAJData();
    QString key =  data->ReadData("API Key");
    if(key != "null")
    {
        ui->apiKeyLine->setText(key);
        ui->SecretKeyLine->setText(data->ReadData("Secret Key"));
    }
    ui->TokenLine->setText((new ISAJData())->ReadData("Accesstoken"));
    QString day = QString::number(system->GetLastTime());
    ui->label->setText(day + "天");
    this->setVisible(true);
}

void BaiduOCR::Connection()
{
    connect(ui->GetBtn, &QPushButton::clicked, this, &BaiduOCR::SetSetting);
    connect(ui->SetBtn, &QPushButton::clicked, this, &QWidget::close);
}
