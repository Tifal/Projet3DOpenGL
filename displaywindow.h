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
    int mouseXStartPosition;
    int mouseYStartPosition;
    int firstMarkerPickedIndex;
    int secondMarkerPickedIndex;


public:
    DisplayWindow(QWidget *parent = Q_NULLPTR);
    int getFirstMarkerPickedIndex() const;
    int getSecondMarkerPickedIndex() const;
    void setViewPort();
    void setProjection();
    void setModelView();
    void setCoordinates(const QVector<Marker>& newCoordinates);
    //void setCoordinates(const QVector<Marker>& newCoordinates);

public slots:
    void resetCamera();

signals:
    void markerPicked();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void pickMarker(QMouseEvent *event);
    void moveCamera(QMouseEvent *event);
};

#endif // DISPLAYWINDOW_H
