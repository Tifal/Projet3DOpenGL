#ifndef COORDINATESWINDOW_H
#define COORDINATESWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
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
    void updateLabelNumber(int index);
    void swapCoordinates(const std::array<int, 2>& markersToBeSwaped);
    //void updateColors(int index);

public slots:
    void removeLineCoordinates();

signals:
    void lineRemoved(int index);

private:
    QGridLayout *layout;
    QVector<QPushButton*> buttonVector;
    QVector<QLabel*> labelVector;
    QVector<QVector<QLineEdit*>> xyzVector;
    QComboBox *distanceMarker1;
    QComboBox *distanceMarker2;
    int colorIndex;
};

#endif // COORDINATESWINDOW_H
