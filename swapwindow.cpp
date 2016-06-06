#include "swapwindow.h"
#include <iostream>

SwapWindow::SwapWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("swap window");
    layout = new QVBoxLayout(this);
    currentStep = 0;
    numberOfFurtherSteps = 10;
    setLayout(layout);
}

void SwapWindow::addSelectedMarker(int index, int color) {
    markerCoordinatesRows.append(new MarkerCoordinatesWidget(markerCoordinatesRows.size(), color, this));
    layout->addWidget(markerCoordinatesRows.last());
    selectedMarkersIndexes.append(index);
    int stepsToAdd = 0;
    if(currentStep + numberOfFurtherSteps + 1 > data->size()) {
        stepsToAdd = data->size() - currentStep;
    }
    else {
        stepsToAdd = numberOfFurtherSteps + 1;
    }
    for(int i = 0 ; i <= numberOfFurtherSteps ; i++) {
        markerCoordinatesRows.last()->addStepCoordinates();
    }
    for(int i = 0 ; i < stepsToAdd ; i++) {
        //markerCoordinatesRows.last()->addStepCoordinates();
        markerCoordinatesRows.last()->setStepCoordinates(i, data->at(currentStep + i).at(index));
    }
}

void SwapWindow::removeSelectedMarker(int index) {
    //attention, il peut y avoir un problème avec les index
    layout->removeWidget(markerCoordinatesRows.at(index));
    delete markerCoordinatesRows.at(index);
    markerCoordinatesRows.remove(index);
    selectedMarkersIndexes.remove(index);
}

void SwapWindow::setData(const QVector<QVector<Marker>> * pointerToData) {
    data = pointerToData;
}

void SwapWindow::updateCoordinates() {
    int furtherStepsToUpdate = numberOfFurtherSteps;
    if(data->size() < currentStep + numberOfFurtherSteps + 1) {
        furtherStepsToUpdate = data->size() - currentStep - 1;
    }
    for(int i = 0 ; i < selectedMarkersIndexes.size() ; i++) {
        for(int j = 0 ; j <= furtherStepsToUpdate ; j++) {
            markerCoordinatesRows.at(i)->setStepCoordinates(j, data->at(currentStep + j).at(selectedMarkersIndexes.at(i)));
        }
        for(int j = furtherStepsToUpdate + 1 ; j < markerCoordinatesRows.last()->getSizeSteps() ; j++) {
            //numberOfFurtherSteps
            markerCoordinatesRows.at(i)->eraseCoordinates(j);
        }
    }
}

void SwapWindow::setCurrentStep(int step) {
    currentStep = step;
}

void SwapWindow::setNumberOfFurtherSteps(int number) {
    int stepsToAddRemove = 0;
    if(number > numberOfFurtherSteps) {
        if(number + currentStep <= data->size()) {
            stepsToAddRemove = number - numberOfFurtherSteps;
            //numberOfFurtherSteps = number;
        }
        else {
            //stepsToAddRemove = data->size() - currentStep;
            numberOfFurtherSteps = numberOfFurtherSteps + data->size() - currentStep;
            stepsToAddRemove = number - numberOfFurtherSteps + 1;
        }
        for(auto markerSelected : markerCoordinatesRows) {
            for(int i = 0 ; i < stepsToAddRemove ; i++) {
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
