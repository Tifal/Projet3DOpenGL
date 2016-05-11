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
    const QVector<Marker>& get1Vector(int index);
    int getDataCoordinatesSize() const;
};

#endif // DATA_H
