#ifndef COORDINATESWINDOW_H
#define COORDINATESWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <cmath>
#include "marker.h"

class CoordinatesWindow : public QWidget
{
    Q_OBJECT
public:
    CoordinatesWindow(QWidget *parent = Q_NULLPTR);
    void setDistance(const Marker& marker1, const Marker& marker2);
    void addLineCoordinates(const Marker& marker, int color);
    void updateCoordinates(QVector<Marker>& markerVector);
    void updateColors(int index);

public slots:
    void removeLineCoordinates();

signals:
    void lineRemoved(int index);

private:
    QGridLayout *layout;
    QVector<QPushButton*> buttonVector;
    QVector<QVector<QLineEdit*>> xyzVector;
    int colorIndex;
};

#endif // COORDINATESWINDOW_H
