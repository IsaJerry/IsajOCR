#include "preset.h"
#include "ui_preset.h"

PreSet::PreSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreSet)
{
    ui->setupUi(this);
    data = new ISAJData();
    Connections();
}

PreSet::~PreSet()
{
    delete ui;
}

void PreSet::LoadData()
{
    QString text;
    preTableLoad(text);
    this->setVisible(true);
}

void PreSet::preTableLoad(QString text)
{
    text = data->ReadData(LoadRow);
    if(text != ISAJ_NULL)
    {
        Row = text.toInt();
        ui->rowLine->setText(text);
    }
    else
    {
        Row = 72;
        ui->rowLine->setText("72");
    }
    text = data->ReadData(LoadColumn);
    if(text != ISAJ_NULL)
    {
        Column = text.toInt();
        ui->columnLine->setText(text);
    }
    else
    {
        Column = 2;
        ui->columnLine->setText("2");
    }
}

void PreSet::SaveData()
{
    data->SaveData(LoadRow, ui->rowLine->text());
    data->SaveData(LoadColumn, ui->columnLine->text());
}

void PreSet::Connections()
{
    connect(ui->okBtn, &QPushButton::clicked, this, [=](){SaveData();this->close();});
    connect(ui->cancelBtn, &QPushButton::clicked, this, [=](){this->close();});
}
