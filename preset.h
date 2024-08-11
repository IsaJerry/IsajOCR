#ifndef PRESET_H
#define PRESET_H

#include "isajdata.h"
#include "ISAJDataNames.h"
#include <QWidget>

namespace Ui {
class PreSet;
}

class PreSet : public QWidget
{
    Q_OBJECT

public:
    explicit PreSet(QWidget *parent = nullptr);
    ~PreSet();

    void LoadData();
    void SaveData();

    void Connections();

    void preTableLoad(QString text);

private:
    Ui::PreSet *ui;

    ISAJData *data;
    int Row, Column;
};

#endif // PRESET_H
