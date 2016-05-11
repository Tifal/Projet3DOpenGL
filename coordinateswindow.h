#ifndef COORDINATESWINDOW_H
#define COORDINATESWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <cmath>
#include "marker.h"

class CoordinatesWindow : public QWidget
{
public:
    CoordinatesWindow(QWidget *parent = Q_NULLPTR);
    void setCoordinatesMarker1(const Marker& marker);
    void setCoordinatesMarker2(const Marker& marker);
    void resetCoordinatesMarker1();
    void resetCoordinatesMarker2();
    void setDistance(const Marker& marker1, const Marker& marker2);

private:
    QGridLayout *layout;
    QLineEdit *x1;
    QLineEdit *y1;
    QLineEdit *z1;
    QLineEdit *x2;
    QLineEdit *y2;
    QLineEdit *z2;
    QLineEdit *distance;
};

#endif // COORDINATESWINDOW_H
#ifndef COORDINATESWINDOW_H
#define COORDINATESWINDOW_H


class CoordinatesWindow
{
public:
    CoordinatesWindow();
};

#endif // COORDINATESWINDOW_H
