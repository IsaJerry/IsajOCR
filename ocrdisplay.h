#ifndef OCRDISPLAY_H
#define OCRDISPLAY_H

#include <QWidget>

namespace Ui {
class OCRDisplay;
}

class OCRDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit OCRDisplay(QWidget *parent = nullptr);
    ~OCRDisplay();

private:
    Ui::OCRDisplay *ui;
};

#endif // OCRDISPLAY_H
