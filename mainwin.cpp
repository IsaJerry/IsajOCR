#include "mainwin.h"
#include "ui_mainwin.h"

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    ui->setupUi(this);
    SetUnits();
    SetWidget();
    Connections();
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::SetUnits()
{
    QList<QLineEdit *> WordsList;
    WordsList << ui->idLine << ui->nameLine;
    QList<QAction *> btn;
    btn << ui->actionAsID << ui->actionAsname;
    table = new TableSet(ui->table, this, ui->searchLine, ui->actionDefaultOpen, ui->actionSave);
    camera = new CameraSet(ui->cameraDisp, ui->cameralistBox, ui->ScreenShot, this, WordsList, btn);
    camera->SetTable(table);
    table->setBottomBar(ui->statusbar);
    baidu = new BaiduOCR();
    preset = new PreSet();
    baidu->GetParent(this);
    camera->SetOcr(baidu->GetOcr());
}

void MainWin::SetWidget()
{
    //ui->cameraWidget->resize(250, 380);
    ui->statusbar->addWidget(new QLabel("v 0.0.0 Alpha"));
}

void MainWin::PreSetPage()
{

}

void MainWin::closeEvent(QCloseEvent *event)
{
    if(table->RetnisNew())
    {
        QMessageBox::StandardButton res = QMessageBox::question(this, "是否保存", "是否保存之后再退出？",
        QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel, QMessageBox::No);
        if(res == QMessageBox::No)
        {
            event->accept();
        }
        else if(res == QMessageBox::Yes)
        {
            table->SaveTable();
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
}

void MainWin::Connections()
{
    connect(ui->actionOpen, &QAction::triggered, table, &TableSet::SetTable);
    connect(ui->actionSave, &QAction::triggered, table, &TableSet::SaveTable);
    connect(ui->actionRecode, &QAction::triggered, table, [=](){table->AddRecode();});
    connect(ui->actionRow, &QAction::triggered, table, [=](){table->AddRow();});
    connect(ui->actionColumn, &QAction::triggered, table, [=](){table->AddColumn();});
    connect(ui->actionSetting, &QAction::triggered, baidu, &BaiduOCR::OpenWidget);
    connect(ui->actionSetIdKeyWord, &QAction::triggered, camera, &CameraSet::SetKeyWord);
    connect(ui->actionNewTable, &QAction::triggered, table, &TableSet::NewTable);
    connect(ui->actionpreSet, &QAction::triggered, preset, &PreSet::LoadData);


    connect(ui->actionAsID, &QAction::triggered, camera, &CameraSet::isUseId);
    connect(ui->actionAsname, &QAction::triggered, camera, &CameraSet::isUseName);
    connect(ui->searchBtn, &QPushButton::clicked, table, &TableSet::SearchDisplay);
    connect(ui->actionDefaultOpen, &QAction::triggered, table, &TableSet::SetDefault);

    connect(ui->cameraOpen, &QPushButton::clicked, camera, &CameraSet::CamaraOpen);
    connect(ui->cameraClose, &QPushButton::clicked, camera, &CameraSet::CameraClose);
    connect(ui->ScreenShot, &QPushButton::clicked, camera, &CameraSet::Screenshot);

}

