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
    QVector<Marker> coordinates;
    QVector<int> selectedMarkerIndexes;
    QVector<int> colorsAvailable;
    int mouseXStartPosition;
    int mouseYStartPosition;

public:
    DisplayWindow(QWidget *parent = Q_NULLPTR);
    void setViewPort();
    void setProjection();
    void setModelView();
    void setCoordinates(const QVector<Marker>& newCoordinates);
    const QVector<int>& getSelectedMarkerIndexes() const;
    //void setCoordinates(const QVector<Marker>& newCoordinates);

public slots:
    void resetCamera();
    void removePickedIndex(int index);

signals:
    //void markerPicked(int index);
    void markerPicked(int index, int color);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void pickMarker();
    bool isSelectedIndex(int index);
    void moveCamera(QMouseEvent *event);
};

#endif // DISPLAYWINDOW_H

