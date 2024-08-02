#ifndef CAMERASET_H
#define CAMERASET_H

#include <Includer.h>

class CameraSet : public QMainWindow
{
public:
    QList<QCameraDevice> cameras;
    QCamera *Camera;

    CameraSet();
    CameraSet(QVideoWidget * cameraDisp, QComboBox *box, QPushButton *srceenshot);
    void SetCamera();
    void CamaraOpen();
    void CameraClose();
    void Screenshot();

private:
    QVideoWidget *CameraDisp;
    QComboBox *cameraBox;
    QMediaCaptureSession capture;
    QImageCapture *imgCapture;
    QPushButton *ScreenShot;

    QStringList GetVideoDeviceList();
    void CameraSelect();
};

#endif // CAMERASET_H
