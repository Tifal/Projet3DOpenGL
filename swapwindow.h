#ifndef SWAPWINDOW_H
#define SWAPWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include "markercoordinateswidget.h"

class SwapWindow : public QWidget
{

    Q_OBJECT
public:
    SwapWindow(QWidget *parent = Q_NULLPTR);
    void addSelectedMarker(int index, int color);
    void removeSelectedMarker(int index);
    void setData(const QVector<QVector<Marker>> * pointerToData);
    void updateCoordinates();
    void setCurrentStep(int step);

public slots:
    void setNumberOfFurtherSteps(int number);

private:
    QVector<MarkerCoordinatesWidget*> markerCoordinatesRows;
    QVBoxLayout *layout;
    const QVector<QVector<Marker>> *data;
    QVector<int> selectedMarkersIndexes;
    int currentStep;
    int numberOfFurtherSteps;
};

#endif // SWAPWINDOW_H
