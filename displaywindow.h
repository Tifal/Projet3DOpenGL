#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <QDebug>
#include <QMatrix4x4>
#include <QFile>
#include <QMouseEvent>

class DisplayWindow : public QOpenGLWidget, protected QOpenGLFunctions_2_0
{
    Q_OBJECT
private:
    QVector<float> coordinates;
    int mouseXStartPosition;
    int mouseYStartPosition;

public:
    DisplayWindow(QWidget *parent = Q_NULLPTR);
    void setViewPort();
    void setProjection();
    void setModelView();
    void setCoordinates(const QVector<float>& newCoordinates);

public slots:
    void resetCamera();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void moveCamera(QMouseEvent *event);
};

#endif // DISPLAYWINDOW_H
