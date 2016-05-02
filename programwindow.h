#ifndef PROGRAMWINDOW_H
#define PROGRAMWINDOW_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include "displaywindow.h"
#include "data.h"

class ProgramWindow : public QWidget
{
    Q_OBJECT

public:
    ProgramWindow();
    void configureScreen();
    void initData(QString& fileName);

public slots:
    void changeStep(int index);
    void launchDemo();
    void demo();

signals:
    void stopTimer();

private:
    QSlider *slider;
    DisplayWindow *screen;
    Data data;
    QLabel *label;
    QPushButton *demoButton;
    QTimer *timer;
};

#endif // PROGRAMWINDOW_H
