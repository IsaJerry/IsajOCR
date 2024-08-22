#include "ocrdisplay.h"
#include "ui_ocrdisplay.h"

OCRDisplay::OCRDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OCRDisplay)
{
    ui->setupUi(this);
}

OCRDisplay::~OCRDisplay()
{
    delete ui;
}
