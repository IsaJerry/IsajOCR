#include "mainwin.h"
#include "ui_mainwin.h"
#include <QSslSocket>

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    ui->setupUi(this);
    camera = new CameraSet(ui->cameraDisp, ui->cameralistBox, ui->ScreenShot);
    table = new TableSet(ui->table, this, ui->searchLine, ui->actionDefaultOpen, ui->actionSave);
    baidu = new BaiduOCR();
    qDebug()<<QSslSocket::sslLibraryBuildVersionString();
    Connections();
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::Connections()
{
    connect(ui->actionOpen, &QAction::triggered, table, &TableSet::SetTable);
    connect(ui->actionSave, &QAction::triggered, table, &TableSet::SaveTable);
    connect(ui->actionRecode, &QAction::triggered, table, &TableSet::AddRecode);
    connect(ui->actionRow, &QAction::triggered, table, &TableSet::AddRow);
    connect(ui->actionColumn, &QAction::triggered, table, &TableSet::AddColumn);
    connect(ui->actionSetting, &QAction::triggered, baidu, &BaiduOCR::OpenWidget);

    connect(ui->searchBtn, &QPushButton::clicked, table, &TableSet::SearchDisplay);
    connect(ui->actionDefaultOpen, &QAction::triggered, table, &TableSet::SetDefault);

    connect(ui->cameraOpen, &QPushButton::clicked, camera, &CameraSet::CamaraOpen);
    connect(ui->cameraClose, &QPushButton::clicked, camera, &CameraSet::CameraClose);
    connect(ui->ScreenShot, &QPushButton::clicked, camera, &CameraSet::Screenshot);

}

