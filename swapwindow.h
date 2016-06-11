#ifndef SWAPWINDOW_H
#define SWAPWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include "markercoordinateswidget.h"

class SwapWindow : public QWidget
{

    Q_OBJECT
public:
    SwapWindow(QWidget *parent = Q_NULLPTR);
    void setData(const QVector<QVector<Marker>> * pointerToData);
    void updateCoordinates();
    void setCurrentStep(int step);

public slots:
    void setNumberOfFurtherSteps(int number);
    void addSelectedMarker(int position, int index, int color);
    void removeSelectedMarker(int position);
    void changeMarkerColorToBeSwapped(int position, int color);

private:
    QVector<MarkerCoordinatesWidget*> markerCoordinatesRows;
    QVBoxLayout *layout;
    const QVector<QVector<Marker>> *data;
    //QVector<int> selectedMarkersIndexes;
    std::array<int, 2> markersToBeSwappedIndexes;
    int currentStep;
    int numberOfFurtherSteps;
};

#endif // SWAPWINDOW_H
