#include "mainwin.h"
#include "ui_mainwin.h"

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    ui->setupUi(this);
    camera = new CameraSet(ui->cameraDisp, ui->cameralistBox);
    table = new TableSet(ui->table, this, ui->searchLine);
    Connections();
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::TableSetting()
{
    table->SetTable();
    ui->actionSave->setEnabled(true);
}

void MainWin::SimpleSearch()
{
    table->SearchDisplay();
}

void MainWin::SaveData()
{
    table->SaveTable();
}

void MainWin::AddRecode()
{
    QString title = QInputDialog::getText(this, "添加一次记录", "输入标题：", QLineEdit::Normal);
    ui->table->setColumnCount(ui->table->columnCount()+1);
    ui->table->setItem(0, ui->table->columnCount()-1, new QTableWidgetItem(title));
}

void MainWin::AddRow()
{
    ui->table->setRowCount(ui->table->rowCount()+1);
}

void MainWin::AddColumn()
{
    ui->table->setColumnCount(ui->table->columnCount()+1);
}

void MainWin::CameraOpen()
{
    ui->cameraDisp->setVisible(true);
    camera->CamaraOpen();
}

void MainWin::CameraClose()
{
    camera->CameraClose();
    ui->cameraDisp->setVisible(false);
}

void MainWin::Connections()
{
    connect(ui->actionOpen, &QAction::triggered, this, &MainWin::TableSetting);
    connect(ui->actionSave, &QAction::triggered, this, &MainWin::SaveData);
    connect(ui->actionRecode, &QAction::triggered, this, &MainWin::AddRecode);
    connect(ui->actionRow, &QAction::triggered, this, &MainWin::AddRow);
    connect(ui->actionColumn, &QAction::triggered, this, &MainWin::AddColumn);

    connect(ui->searchBtn, &QPushButton::clicked, this, &MainWin::SimpleSearch);
    connect(ui->cameraOpen, &QPushButton::clicked, this, &MainWin::CameraOpen);
    connect(ui->cameraClose, &QPushButton::clicked, this, &MainWin::CameraClose);
}

