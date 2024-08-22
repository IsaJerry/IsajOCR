#ifndef MAINWIDGETSPLITTER_H
#define MAINWIDGETSPLITTER_H

#include <QSplitter>

class MainWidgetSplitter
{
public:
    MainWidgetSplitter();
    void AddWidget(QWidget *widget);
    void AddWidgets(QList<QWidget *> widgets);
    void ReplaceParent(QWidget *widget);

private:
    QSplitter *Splitter;
};

#endif // MAINWIDGETSPLITTER_H
