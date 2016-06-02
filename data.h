#ifndef DATA_H
#define DATA_H

#include <QVector>
#include <QFile>
#include <iostream>
#include "marker.h"

class Data
{

private:
    QVector<QVector<Marker>> dataCoordinates;
    int indexCurrentStep;   //????

public:
    Data();
    void displayData() const;
    void loadData(QString& fileName);
    //const QVector<float>& get1Vector(int index);
    const QVector<QVector<Marker>>* getDataCoordinates();
    const QVector<Marker>& get1Vector(int index) const;
    const Marker& get1Marker(int step, int index) const;
    int getDataCoordinatesSize() const;
    void swapMarkersData(const std::array<int, 2>& markersIndexes, int step);
};

#endif // DATA_H

