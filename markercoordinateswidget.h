#ifndef MARKERCOORDINATESWIDGET_H
#define MARKERCOORDINATESWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include "marker.h"

class MarkerCoordinatesWidget : public QFrame
{
public:
    MarkerCoordinatesWidget(int number, int color, QWidget *parent = Q_NULLPTR);
    ~MarkerCoordinatesWidget();
    void setStepCoordinates(int step, const Marker& marker);
    void eraseCoordinates(int step);
    void addStepCoordinates();
    void removeStepCoordinates();
    int getSizeSteps();
    void setMarkerNumber(int number);
    void setMarkerColor(int color);
    void addStepLabel();
    void removeStepLabel();
    void updateStepLabel(int index, int stepNumber);

private:
    QLabel * markerNumber;
    QLabel * x;
    QLabel * y;
    QLabel * z;
    QLabel *timeStep;
    QLineEdit * markerColor;
    std::array<QVector<QLineEdit *>, 3> coordinatesColumns;
    QVector<QLabel *> timeStepsLabels;
    QGridLayout *layout;
};

#endif // MARKERCOORDINATESWIDGET_H
