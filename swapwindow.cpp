#include "swapwindow.h"
#include <iostream>

SwapWindow::SwapWindow(QWidget *parent) : QWidget(parent)
{
    /*QScrollArea *scrollArea = new QScrollArea(parent);
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scrollArea->setWidgetResizable(true);*/
    setGeometry(500, 500, 100, 100);
    //scrollArea->setGeometry(500, 500, 600, 400);
    setWindowTitle("swap window");
    layout = new QVBoxLayout(this);
    currentStep = 0;
    numberOfFurtherSteps = 10;
    layout->setSpacing(0);
    setLayout(layout);
    for(int i = 0 ; i < 2 ; i++) {
        markersToBeSwappedIndexes[i] = -1;
    }
    //scrollArea->setWidget(this);
    //scrollArea->setLayout(layout);
    //scrollArea->show();
}

void SwapWindow::addSelectedMarker(int position, int index, int color) {
    if(color != -1) {
        markerCoordinatesRows.append(new MarkerCoordinatesWidget(markerCoordinatesRows.size(), color, this));
    }
    else {
        markerCoordinatesRows.append(new MarkerCoordinatesWidget(markerCoordinatesRows.size(), Qt::white, this));
    }
    layout->addWidget(markerCoordinatesRows.last());
    //selectedMarkersIndexes.append(index);
    markersToBeSwappedIndexes[position] = index;
    for(int i = 0 ; i <= numberOfFurtherSteps ; i++) {
        markerCoordinatesRows.last()->addStepCoordinates();
        markerCoordinatesRows.last()->setStepCoordinates(i, data->get1Marker(currentStep + i, index));
    }
    layout->addStretch(1);
}

void SwapWindow::removeSelectedMarker(int position) {
    //attention, il peut y avoir un problème avec les index
    layout->removeWidget(markerCoordinatesRows.at(position));
    delete markerCoordinatesRows.at(position);
    markerCoordinatesRows.remove(position);
    //selectedMarkersIndexes.remove(position);
    markersToBeSwappedIndexes[position] = -1;
    if(position == 0 && markersToBeSwappedIndexes[1] != -1) {
        markerCoordinatesRows.last()->setMarkerNumber(1);
    }
}

void SwapWindow::setData(const Data * pointerToData) {
    data = pointerToData;
}

void SwapWindow::updateCoordinates() {
    for(int i=0; i<2;i++){
        if(markersToBeSwappedIndexes.at(i)!=-1){
            for(int j = 0 ; j <= numberOfFurtherSteps ; j++) {
                markerCoordinatesRows.at(i)->setStepCoordinates(j, data->get1Marker(currentStep + j, markersToBeSwappedIndexes.at(i)));
            }
        }
    }
}

void SwapWindow::setCurrentStep(int step) {
    currentStep = step;
}

void SwapWindow::setNumberOfFurtherSteps(int number) {
    if(number > numberOfFurtherSteps) {
        for(auto markerSelected : markerCoordinatesRows) {
            for(int i = 0 ; i < number - numberOfFurtherSteps ; i++) {
                markerSelected->addStepCoordinates();
            }
        }
        numberOfFurtherSteps = number;
        updateCoordinates();
    }
    else {
        for(auto markerSelected : markerCoordinatesRows) {
            for(int i = 0 ; i < numberOfFurtherSteps - number ; i++) {
                markerSelected->removeStepCoordinates();
            }
        }
        numberOfFurtherSteps = number;
    }
}

void SwapWindow::changeMarkerColorToBeSwapped(int position, int color) {
    markerCoordinatesRows.at(position)->setMarkerColor(color);
}
