#ifndef DATA_H
#define DATA_H

#include <QVector>
#include <QFile>
#include <iostream>
#include <QTextStream>
#include "marker.h"

class Data
{

private:
    // QVector that stores coordinates of the markers for each time step
    // 2 dimensionnal QVector where the rows corresponds to the time steps and the columns corresponds to the markers
    QVector<QVector<Marker>> dataCoordinates;
    int indexCurrentStep;   //????

public:
    Data();
    void displayData() const;
    void loadData(QString& fileName);
    void saveData(QString& fileName);
    //const QVector<float>& get1Vector(int index);
    const QVector<QVector<Marker>>* getDataCoordinates() const;
    const QVector<Marker>& get1Vector(int index) const;
    const Marker& get1Marker(int step, int index) const;
    int getDataCoordinatesSize() const;
    void swapMarkersData(const std::array<int, 2>& markersIndexes, int step);
};

#endif // DATA_H

