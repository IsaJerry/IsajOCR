#ifndef CAMERASET_H
#define CAMERASET_H

#include "ocrsystem.h"
#include <Includer.h>

class CameraSet : public QMainWindow
{
public:
    QList<QCameraDevice> cameras;
    QCamera *Camera;

    CameraSet();
    CameraSet(QVideoWidget * cameraDisp, QComboBox *box, QPushButton *srceenshot, QWidget *parent);
    void SetCamera();
    void CamaraOpen();
    void CameraClose();
    void Screenshot();
    void SetOcr(OCRSystem *system);

private:
    QWidget *parent;
    QVideoWidget *CameraDisp;
    QComboBox *cameraBox;
    QMediaCaptureSession capture;
    QImageCapture *imgCapture;
    QPushButton *ScreenShot;
    QString ImageData;
    OCRSystem *system;

    QStringList GetVideoDeviceList();
    void CameraSelect();
};

#endif // CAMERASET_H
