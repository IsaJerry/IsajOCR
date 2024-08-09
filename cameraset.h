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


    enum SearchType
    {
        UseId = 1,
        UseName = 2
    };

    CameraSet();
    CameraSet(QVideoWidget * cameraDisp, QComboBox *box, QPushButton *srceenshot, QWidget *parent, QList<QLineEdit *> WordsList, QList<QAction *> uselist);
    void SetCamera();
    void SetTable(TableSet *table);
    void SetUseSearchBtn(QList<QAction *> uselist);
    void CamaraOpen();
    void CameraClose();
    void Screenshot();
    void SetOcr(OCRSystem *system);

    void SetSearchBtn();
    void isUseId(bool checked);
    void isUseName(bool checked);

    void SetKeyWord();
    void GetKeyWord();
    
    void GetOCRresult(int id, const QImage &preview);
    void SetDisplay();
    void SearchUse(enum SearchType type, QString text);
    bool isPairing(QString text, enum SearchType type);
    
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
    QList<QAction *> SearchUseList;

    QStringList GetVideoDeviceList();
    void CameraSelect();
};

#endif // CAMERASET_H
