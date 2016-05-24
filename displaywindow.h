#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <QDebug>
#include <QMatrix4x4>
#include <QFile>
#include <QMouseEvent>
#include "marker.h"

class DisplayWindow : public QOpenGLWidget, protected QOpenGLFunctions_2_0
{
    Q_OBJECT
private:
    const QVector<QVector<Marker>> * data;
    QVector<int> selectedMarkerIndexes;
    QVector<int> colorsAvailable;
    QVector<std::array<int, 2>> linkedMarkersIndexes;
    int currentStep;
    int mouseXStartPosition;
    int mouseYStartPosition;
    bool displayFormerSteps;
    bool linkMarkerMode;
    bool selectMarkerMode;
    bool lineBeingDrawn;

public:
    DisplayWindow(QWidget *parent = Q_NULLPTR);
    void setViewPort();
    void setProjection();
    void setModelView();
    void setData(const QVector<QVector<Marker>> * pointerToData);
    void setCurrentStep(int index);
    const QVector<int>& getSelectedMarkerIndexes() const;
    void selectMarker();
    void linkMarkerLine();
    void setLinkMarkerMode(bool boolean);
    void setSelectMarkerMode(bool boolean);
    void setDisplayFormerSteps(bool boolean);
    const Marker& getMarkerWithCross() const;
    bool alreadyLinkedMarkers(std::array<int, 2>& linkedMarkers);
    //void setCoordinates(const QVector<Marker>& newCoordinates);

public slots:
    void resetCamera();
    void removePickedIndex(int index);
    void resetLinkedMarkersIndexes();

signals:
    //void markerPicked(int index);
    void markerPicked(int index, int color);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void paintAxes();
    void paintMarkers();
    void paintSelectedMarkers();
    void paintLinkedMarkers();
    void paintFormerSteps();
    void paintMarkerWithCross();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int pickMarker();
    bool isSelectedIndex(int index);
    void moveCamera(QMouseEvent *event);
};

#endif // DISPLAYWINDOW_H

