#ifndef PROGRAMWINDOW_H
#define PROGRAMWINDOW_H

#include <QWidget>
#include <QSlider>
#include <QGridLayout>
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

public slots:
    void changeStep(int index);
    void demoPlaying();
    void startDemo();
    void pauseDemo();
    void stopDemo();

signals:
    void stopTimer();

private:
    QSlider *slider;
    DisplayWindow *screen;
    Data data;
    QLabel *label;
    QPushButton *demoButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QTimer *timer;
};

#endif // PROGRAMWINDOW_H