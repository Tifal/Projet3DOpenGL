#ifndef PROGRAMWINDOW_H
#define PROGRAMWINDOW_H

#include <QWidget>
#include <QSlider>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include "displaywindow.h"
#include "data.h"
#include "coordinateswindow.h"
#include "filewindow.h"

class ProgramWindow : public QWidget
{
    Q_OBJECT

public:
    ProgramWindow();
    void configureScreen();
    void updateWindowCoordinates();

public slots:
    void changeStep(int index);
    void fillWindowCoordinates(int index, int color);
    void demoPlaying();
    void startDemo();
    void pauseDemo();
    void stopDemo();
    void displayFile();
    void changeChoice1();
    void changeChoice2();
    void selectOrLinkMode();
    void enableDisplayFormerSteps();
    void enableDisplayFurtherSteps();
    void choosePointsLinesFormerSteps();

signals:
    void stopTimer();

private:
    QSlider *slider;
    DisplayWindow *screen;
    CoordinatesWindow *coordinatesWindow;
    FileWindow *filewindow;
    Data data;
    QLabel *label;
    QPushButton *demoButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QPushButton *displayFileCoordinates;
    QPushButton *selectModeButton;
    QPushButton *linkModeButton;
    QPushButton *formerSteps;
    QPushButton *furtherSteps;
    QRadioButton *displayChoice1;
    QRadioButton *displayChoice2;
    QRadioButton *formerStepsLine;
    QRadioButton *formerStepsPoints;
    QComboBox *numberOfFormerSteps;
    QComboBox *numberOfFurtherSteps;
    QTimer *timer;
};

#endif // PROGRAMWINDOW_H
