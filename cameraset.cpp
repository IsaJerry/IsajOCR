#include "cameraset.h"

CameraSet::CameraSet()
{

}

CameraSet::CameraSet(QVideoWidget *cameraDisp, QComboBox *box, QPushButton *srceenshot)
{
    this->CameraDisp = cameraDisp;
    this->cameraBox = box;
    this->ScreenShot = srceenshot;
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

void CameraSet::Screenshot()
{
    imgCapture->capture();
    connect(imgCapture, &QImageCapture::imageCaptured, this, [=](int id, const QImage &preview){
        QPixmap a;
        a.convertFromImage(preview);
    });
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
