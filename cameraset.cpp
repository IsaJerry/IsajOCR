#include "cameraset.h"
#include "fileop.h"

CameraSet::CameraSet()
{

}

CameraSet::CameraSet(QVideoWidget *cameraDisp, QComboBox *box, QPushButton *srceenshot, QWidget *parent,
                     QList<QLineEdit *> WordsList, QList<QAction *> uselist)
{
    this->CameraDisp = cameraDisp;
    this->cameraBox = box;
    this->ScreenShot = srceenshot;
    this->parent = parent;
    file = new FileOp(parent);
    this->WordsList = WordsList;
    SetUseSearchBtn(uselist);
    GetKeyWord();
    SetSearchBtn();
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
    if(!table->RetnOcrColumn())
    {
        QMessageBox::warning(parent, "提示", "请先设置OCR目标列");
        disconnect(imgCapture, &QImageCapture::imageCaptured, this, &CameraSet::GetOCRresult);
        return;
    }
    ID = id;
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
        if((new ISAJData())->ReadData(USE_ID) == ISAJ_TRUE)
        {
            SearchUse(UseId, WordList.at(i));
        }
        else if((new ISAJData())->ReadData(USE_NAME) == ISAJ_TRUE)
        {
            SearchUse(UseName, WordList.at(i));
        }
        else
        {
            QMessageBox::warning(parent, "ERROR", "未设置搜索方式");
            break;
        }
    }
    disconnect(imgCapture, &QImageCapture::imageCaptured, this, &CameraSet::GetOCRresult);
}

void CameraSet::SearchUse(SearchType type, QString text)
{
    switch(type)
    {
        case UseId:
            if(isPairing(text, UseId))
            {
                WordsList.at(0)->setText(text);
                table->OcrSearch(text);
                return;
            }
            WordsList.at(1)->setText(text);
            return;
        case UseName:
            if(isPairing(text, UseName))
            {
                WordsList.at(1)->setText(text);
                table->OcrSearch(text);
                return;
            }
            WordsList.at(0)->setText(text);
            return;
        default:
            break;
    }
}

bool CameraSet::isPairing(QString text, SearchType type)
{
    switch (type)
    {
        case UseId:
            if(IdKeyWord == "not set" || IdKeyWord == "")
            {
                QMessageBox::warning(parent, "ERROR", "未设置学号关键字");
                return false;
            }
            if(text.contains(IdKeyWord, Qt::CaseSensitive))
            {
                return true;
            }
            return false;
            break;
        case UseName:
            if(table->RetnSearchTipList().contains(text))
            {
                return true;
            }
            return false;
            break;
        default:
            return false;
            break;
        }
}

int CameraSet::RetnImgNO()
{
    return ID;
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

void CameraSet::SetSearchBtn()
{
    ISAJData *data = new ISAJData();
    if(data->ReadData(USE_ID) == ISAJ_NULL)
    {
        SearchUseList.at(0)->setChecked(true);
        SearchUseList.at(1)->setChecked(false);
        return;
    }
    if(data->ReadData(USE_ID) == ISAJ_TRUE)
    {
        SearchUseList.at(0)->setChecked(true);
        SearchUseList.at(1)->setChecked(false);
        return;
    }
    if(data->ReadData(USE_NAME) == ISAJ_TRUE)
    {
        SearchUseList.at(0)->setChecked(false);
        SearchUseList.at(1)->setChecked(true);
        return;
    }
}

void CameraSet::isUseId(bool checked)
{
    ISAJData *data = new ISAJData();
    if(checked)
    {
        if(SearchUseList.at(1)->isChecked())
        {
            SearchUseList.at(1)->setChecked(false);
            isUseName(false);
        }
        data->SaveData(USE_ID, ISAJ_TRUE);
    }
    else
    {
        data->SaveData(USE_ID, ISAJ_FALSE);
    }
}

void CameraSet::isUseName(bool checked)
{
    ISAJData *data = new ISAJData();
    if(checked)
    {
        if(SearchUseList.at(0)->isChecked())
        {
            SearchUseList.at(0)->setChecked(false);
            isUseId(false);
        }
        data->SaveData(USE_NAME, ISAJ_TRUE);
    }
    else
    {
        data->SaveData(USE_NAME, ISAJ_FALSE);
    }
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
    (new ISAJData())->SaveData(ID_KEY_WORD, IdKeyWord);
}

void CameraSet::GetKeyWord()
{
    IdKeyWord = (new ISAJData())->ReadData(ID_KEY_WORD);
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

void CameraSet::SetUseSearchBtn(QList<QAction *> uselist)
{
    this->SearchUseList = uselist;
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
