#include "cameraset.h"

CameraSet::CameraSet()
{

}

CameraSet::CameraSet(QVideoWidget *cameraDisp, QComboBox *box)
{
    this->CameraDisp = cameraDisp;
    this->cameraBox = box;
    CameraSelect();
}

void CameraSet::CamaraOpen()
{
    SetCamera();
    Camera->start();
}

void CameraSet::CameraClose()
{
    if(Camera->isActive())
    {
        Camera->stop();
    }
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
