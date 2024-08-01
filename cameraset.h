#ifndef CAMERASET_H
#define CAMERASET_H

#include <Includer.h>

class CameraSet
{
public:
    QList<QCameraDevice> cameras;
    QCamera *Camera;

    CameraSet();
    CameraSet(QVideoWidget * cameraDisp, QComboBox *box);
    void SetCamera();
    void CamaraOpen();
    void CameraClose();

private:
    QVideoWidget *CameraDisp;
    QComboBox *cameraBox;
    QMediaCaptureSession capture;

    QStringList GetVideoDeviceList();
    void CameraSelect();
};

#endif // CAMERASET_H
