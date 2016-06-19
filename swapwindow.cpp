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
    numberOfFurtherSteps = 0;
    numberOfFurtherStepsToUpdate = 0;
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
    for(int i = 0 ; i <= numberOfFurtherStepsToUpdate ; i++) {
        markerCoordinatesRows.last()->addStepLabel();
        markerCoordinatesRows.last()->updateStepLabel(i, currentStep + i + 1);
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
            for(int j = 0 ; j <= numberOfFurtherStepsToUpdate ; j++) {
                markerCoordinatesRows.at(i)->updateStepLabel(j, currentStep + j + 1);
                markerCoordinatesRows.at(i)->setStepCoordinates(j, data->get1Marker(currentStep + j, markersToBeSwappedIndexes.at(i)));
            }
        }
    }
}

void SwapWindow::setCurrentStep(int step) {
    currentStep = step;
    if(!(data->getDataCoordinatesSize() - 1 > currentStep + numberOfFurtherSteps)) {
        if(numberOfFurtherStepsToUpdate < data->getDataCoordinatesSize() - currentStep - 1) {
            for(auto markerToBeSwapped : markerCoordinatesRows) {
                while(markerToBeSwapped->getSizeSteps() <= data->getDataCoordinatesSize() - currentStep - 1) {
                    markerToBeSwapped->addStepCoordinates();
                    markerToBeSwapped->addStepLabel();
                }
            }
        }
        else {
            for(auto markerToBeSwapped : markerCoordinatesRows) {
                while(markerToBeSwapped->getSizeSteps() > data->getDataCoordinatesSize() - currentStep) {
                    markerToBeSwapped->removeStepCoordinates();
                    markerToBeSwapped->removeStepLabel();
                }
            }
        }
        numberOfFurtherStepsToUpdate = data->getDataCoordinatesSize() - currentStep - 1;
    }
    else {
        for(auto markerToBeSwapped : markerCoordinatesRows) {
            while(markerToBeSwapped->getSizeSteps() <= numberOfFurtherSteps) {
                markerToBeSwapped->addStepCoordinates();
                markerToBeSwapped->addStepLabel();
            }
        }
        numberOfFurtherStepsToUpdate = numberOfFurtherSteps;
    }
    updateCoordinates();
}

void SwapWindow::setNumberOfFurtherSteps(int number) {
    if(number > numberOfFurtherSteps) {
        int numberOfColumnsToAdd = 0;
        if(data->getDataCoordinatesSize() > number + currentStep) {
            numberOfColumnsToAdd = number - numberOfFurtherSteps;
            numberOfFurtherStepsToUpdate = number;
        }
        else {
            numberOfColumnsToAdd = data->getDataCoordinatesSize() - (currentStep + numberOfFurtherSteps) - 1;
            numberOfFurtherStepsToUpdate = data->getDataCoordinatesSize() - currentStep - 1;
        }
        for(auto markerToBeSwapped : markerCoordinatesRows) {
            for(int i = 0 ; i < numberOfColumnsToAdd ; i++) {
                markerToBeSwapped->addStepCoordinates();
                markerToBeSwapped->addStepLabel();
            }
        }
        updateCoordinates();
    }
    else {
        if(data->getDataCoordinatesSize() > number + currentStep) {
            for(auto markersToBeSwapped : markerCoordinatesRows) {
                for(int i = 0 ; i < numberOfFurtherStepsToUpdate - number ; i++) {
                    markersToBeSwapped->removeStepCoordinates();
                    markersToBeSwapped->removeStepLabel();
                }
            }
            numberOfFurtherStepsToUpdate = number;
        }
        else {
            numberOfFurtherStepsToUpdate = data->getDataCoordinatesSize() - currentStep - 1;
        }
    }
    numberOfFurtherSteps = number;
}

void SwapWindow::changeMarkerColorToBeSwapped(int position, int color) {
    markerCoordinatesRows.at(position)->setMarkerColor(color);
}

int SwapWindow::getNumberOfFurtherStepsToUpdate() {
    return numberOfFurtherStepsToUpdate;
}
