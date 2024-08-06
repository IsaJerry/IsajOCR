#ifndef CAMERASET_H
#define CAMERASET_H

#include "fileop.h"
#include "ocrsystem.h"
#include "tableset.h"
#include <Includer.h>

class CameraSet : public QMainWindow
{
public:
    QList<QCameraDevice> cameras;
    QCamera *Camera;

    CameraSet();
    CameraSet(QVideoWidget * cameraDisp, QComboBox *box, QPushButton *srceenshot, QWidget *parent, QList<QLineEdit *> WordsList);
    void SetCamera();
    void SetTable(TableSet *table);
    void CamaraOpen();
    void CameraClose();
    void Screenshot();
    void SetOcr(OCRSystem *system);

    void SetKeyWord();
    void GetKeyWord();
    
    void GetOCRresult(int id, const QImage &preview);
    void SetDisplay();
    
private:
    QWidget *parent;
    QVideoWidget *CameraDisp;
    QComboBox *cameraBox;
    QMediaCaptureSession capture;
    QImageCapture *imgCapture;
    QPushButton *ScreenShot;
    QString ImageData;
    OCRSystem *system;
    TableSet *table;

    FileOp *file;

    QString IdKeyWord;
    QList<QLineEdit *> WordsList;

    QStringList GetVideoDeviceList();
    void CameraSelect();
};

#endif // CAMERASET_H
