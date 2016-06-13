#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <QDebug>
#include <QMatrix4x4>
#include <QFile>
#include <QMouseEvent>
#include "data.h"
#include "marker.h"

class DisplayWindow : public QOpenGLWidget, protected QOpenGLFunctions_2_0
{
    Q_OBJECT
private:
    // a pointer to the data from the Data class of the program
    //const QVector<QVector<Marker>> * data;
    const Data *data;
    // QVector storing the index of the markers that have been picked in select mode
    QVector<int> selectedMarkerIndexes;
    // QVector storing the color available to display the selected markers
    // colorsAvailable.at(0) is the color of selectedMarkerIndexes.at(0), colorsAvailable.at(1) is selectedMarkerIndexes.at(1) and so on.
    QVector<int> colorsAvailable;
    // QVector that stores arrays holding the two marker-indexes that are linked to each other by a line in link mode
    QVector<std::array<int, 2>> linkedMarkersIndexes;
    // QVector that stores the indexes of the markers that have been picked in swap mode
    std::array<int, 2> markersToBeSwapedIndexes;
    int currentStep;
    // the x position of the mouse on the screen
    int mouseXStartPosition;
    // the y position of the mouse on the screen
    int mouseYStartPosition;
    int numberOfFormerStepsDisplayed;
    int numberOfFurtherStepsDisplayed;
    // a boolean that indicates whether the previous steps must be painted on the screen or not
    bool displayFormerSteps;
    bool formerStepsSelectedMarkers;
    // a boolean that shows whether the future steps must be painted on the screen or not
    bool displayFurtherSteps;
    // a boolean that indicates if the current mode is link mode to know how to process the marker picked
    bool linkMarkerMode;
    // a boolean that indicates whether skeleton of links must be painted on the screen or not
    bool displayLinks;
    // a boolean that shows if the current mode is select mode to know how to process the marker picked
    bool selectMarkerMode;
    // a boolean that indicates if the current mode is swap mode to know how to process the marker picked
    bool swapMode;
    bool eraseOneLinkMode;
    // a boolean that is used to know if the white cross should be painted on the screen
    bool lineBeingDrawn;
    // a boolean that indicates whether the previous steps should be displayed as points or lines
    bool formerStepsPoints;

public:
    DisplayWindow(QWidget *parent = Q_NULLPTR);
    void setViewPort();
    void setProjection();
    void setModelView();
    void setData(const Data * pointerToData);
    void setCurrentStep(int index);
    const QVector<int>& getSelectedMarkerIndexes() const;
    const std::array<int, 2>& getMarkersToBeSwaped() const;
    void selectMarker();
    void linkMarkerLine();
    int pickLink();
    void removePickedLink();
    void swapMarkers();
    void setLinkMarkerMode(bool boolean);
    void setEraseOneLinkMode(bool boolean);
    void setSwapMode(bool boolean);
    void setDisplayLinks(bool boolean);
    void setSelectMarkerMode(bool boolean);
    void setDisplayFormerSteps(bool boolean);
    void setDisplayFurtherSteps(bool boolean);
    void setFormerStepsPoints(bool boolean);
    void setFormerStepsSelectedMarkers(bool boolean);
    const Marker& getMarkerWithCross() const;
    const QVector<std::array<int, 2>>& getLinkedMarkersIndexes() const;
    bool alreadyLinkedMarkers(std::array<int, 2>& linkedMarkers);
    //void setCoordinates(const QVector<Marker>& newCoordinates);

public slots:
    void resetCamera();
    void moveCameraToLeftSide();
    void moveCameraToFrontSide();
    void moveCameraToBackSide();
    void moveCameraToRightSide();
    void removePickedIndex(int index);
    void resetLinkedMarkersIndexes();
    void setNumberOfFormerStepsDisplayed(int number);
    void setNumberOfFurtherStepsDisplayed(int number);

signals:
    //void markerPicked(int index);
    void markerPicked(int index, int color);
    void markerToBeSwappedPicked(int position, int index, int color);
    void removeMarkerToBeSwapped(int position);
    void changeColorMarkerToBeSwapped(int position, int color);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void paintAxes();
    void paintMarkers();
    void paintSelectedMarkers();
    void paintLinkedMarkers();
    void paintFormerSteps();
    void paintFurtherSteps();
    void paintMarkerWithCross();
    void paintMarkersWithRedCross();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int pickMarker();
    void moveCamera(QMouseEvent *event);
};

#endif // DISPLAYWINDOW_H

