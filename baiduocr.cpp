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

void BaiduOCR::GetParent(QWidget *parent)
{
    this->parent = parent;
}

void BaiduOCR::SetWidget()
{
    this->setFixedSize(330, 210);
}

void BaiduOCR::SetSetting()
{
    if(ui->TokenLine->text() != "")
    {
        ui->TokenLine->clear();
    }
    QString reasult = system->getAccessToken(ui->apiKeyLine->text(), ui->SecretKeyLine->text());
    if(reasult != "success")
    {
        QMessageBox::warning(this, "ERROR", reasult);
        return;
    }
    QMessageBox::information(this, "消息", "获取成功");
    this->close();
}

void BaiduOCR::OpenWidget()
{
    ISAJData *data = new ISAJData();
    QString key =  data->ReadData(API_KEY);
    if(key != ISAJ_NULL)
    {
        ui->apiKeyLine->setText(key);
        ui->SecretKeyLine->setText(data->ReadData(SECRET_KEY));
    }
    key = data->ReadData(ACCESS_TOKEN);
    if(key != ISAJ_NULL)
    {
        ui->TokenLine->setText(key);
    }
    QString day = QString::number(system->GetLastTime());
    ui->label->setText(day + "天");
    key = data->ReadData(LAST_COUNT);
    this->setVisible(true);
}

OCRSystem *BaiduOCR::GetOcr()
{
    return system;
}

void BaiduOCR::Connection()
{
    connect(ui->GetBtn, &QPushButton::clicked, this, &BaiduOCR::SetSetting);
    connect(ui->SetBtn, &QPushButton::clicked, this, &QWidget::close);
}
