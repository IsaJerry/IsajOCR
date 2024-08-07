#include "cameraset.h"
#include "fileop.h"

CameraSet::CameraSet()
{

}

CameraSet::CameraSet(QVideoWidget *cameraDisp, QComboBox *box, QPushButton *srceenshot, QWidget *parent, QList<QLineEdit *> WordsList)
{
    this->CameraDisp = cameraDisp;
    this->cameraBox = box;
    this->ScreenShot = srceenshot;
    this->parent = parent;
    file = new FileOp(parent);
    this->WordsList = WordsList;
    GetKeyWord();
    CameraSelect();
}

void CameraSet::CamaraOpen()
{
    CameraDisp->setVisible(true);
    SetCamera();
    Camera->start();
    ScreenShot->setEnabled(true);
}

void CameraSet::CameraClose()
{
    if(Camera->isActive())
    {
        Camera->stop();
    }
    CameraDisp->setVisible(false);
    ScreenShot->setEnabled(false);
}

void CameraSet::GetOCRresult(int id, const QImage &preview)
{
    ImageData = file->Image2Base64(preview);
    QString data = system->HandWriting(ImageData);
    if(data != "success")
    {
        QMessageBox::information(parent, "info", data);
    }
    SetDisplay();
}

void CameraSet::SetDisplay()
{
    QStringList WordList = system->GetWordsList();
    WordsList.at(0)->setText("");
    WordsList.at(1)->setText("");
    for (int i = 0; i < WordList.length(); i++)
    {
        if(WordList.at(i).contains(IdKeyWord, Qt::CaseSensitive))
        {
            WordsList.at(0)->setText(WordList.at(i));
            table->OcrSearch(WordList.at(i));
            continue;
        }
        WordsList.at(1)->setText(WordList.at(i));
    }
    disconnect(imgCapture, &QImageCapture::imageCaptured, this, &CameraSet::GetOCRresult);
}

void CameraSet::Screenshot()
{
    imgCapture->capture();
    connect(imgCapture, &QImageCapture::imageCaptured, this, &CameraSet::GetOCRresult);
}

void CameraSet::SetOcr(OCRSystem *system)
{
    this->system = system;
}

void CameraSet::SetKeyWord()
{
    QString keyword;
    if(IdKeyWord == "null")
    {
        keyword = file->OpenDialog(FileOp::KeyWord);
        if(keyword == "null")
        {
            return;
        }
    }
    else
    {
        keyword = file->OpenDialog(FileOp::KeyWord, IdKeyWord);
        if(keyword == "null")
        {
            return;
        }
    }
    IdKeyWord = keyword;
    (new ISAJData())->SaveData("IdKeyWord", IdKeyWord);
}

void CameraSet::GetKeyWord()
{
    IdKeyWord = (new ISAJData())->ReadData("IdKeyWord");
}

void CameraSet::SetCamera()
{
    for(QCameraDevice &cameraDevice : cameras)
    {
        if(cameraDevice.description() == cameraBox->currentText())
        {
            Camera = new QCamera(cameraDevice);
        }
    }
    capture.setCamera(Camera);
    imgCapture = new QImageCapture();
    imgCapture->setParent(Camera);
    capture.setImageCapture(imgCapture);
    capture.setVideoOutput(CameraDisp);
}

void CameraSet::SetTable(TableSet *table)
{
    this->table = table;
}

QStringList CameraSet::GetVideoDeviceList()
{
    QStringList cameraList;
    cameras = QMediaDevices::videoInputs();
    for(QCameraDevice &cameraDevice : cameras)
    {
        cameraList<<cameraDevice.description();
    }
    return cameraList;
}

void CameraSet::CameraSelect()
{
    cameraBox->addItems(GetVideoDeviceList());
}
