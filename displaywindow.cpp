#include "displaywindow.h"
#include <iostream>

using namespace std;

/** Constructor to initialize the window.
 * @brief DisplayWindow::DisplayWindow
 * @param parent
 */

DisplayWindow::DisplayWindow(QWidget *parent) : QOpenGLWidget(parent) { }

/** Method that sets the viewport of the window.
 * @brief DisplayWindow::setViewPort
 */

void DisplayWindow::setViewPort() {
    glViewport(0, 0, width(), height());
}

/** Method that sets the projection matrix.
 * @brief DisplayWindow::setProjection
 */

void DisplayWindow::setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    QMatrix4x4 projection;
    projection.perspective(70.0, (double)width() / (double)height(), 1.0, 20.0);
    float * tab = projection.data();
    glMultMatrixf(tab);
}

/** Method that sets the model and view matrix.
 * @brief DisplayWindow::setModelView
 */

void DisplayWindow::setModelView() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    QMatrix4x4 view;
    view.lookAt(QVector3D(2, 2, 0.5), QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 0.0, 1.0));
    float * tab = view.data();
    glMultMatrixf(tab);
}

/** Method that sets the
 * @brief DisplayWindow::setCoordinates
 * @param newCoordinates
 */

void DisplayWindow::setCoordinates(const QVector<float>& newCoordinates) {
    coordinates = newCoordinates;
}

/** Method to initialize and use OpenGL.
 * @brief DisplayWindow::initializeGL
 */

void DisplayWindow::initializeGL()
{
    initializeOpenGLFunctions();//THIS MUST BE CALLED TO INIT OPENGL
    qDebug() << "initializeGL()";
}

/** Method called when the window is resized.
 * @brief DisplayWindow::resizeGL
 * @param w
 * @param h
 */

void DisplayWindow::resizeGL(int w, int h){}

/** Method that is called when the window is painted.
 * @brief DisplayWindow::paintGL
 */

void DisplayWindow::paintGL()
{
    qDebug() << "paintGL";

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(2.0);
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);

    for(int i = 0 ; i < coordinates.size() ; i += 3) {
        glVertex3f(coordinates.at(i) / 1500, coordinates.at(i + 1) /1500, coordinates.at(i + 2) /1500);
    }
    glEnd();

    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1.0);
    glEnd();

    glFlush();
}

/** Method that implements the mouse pressed event.
 * @brief DisplayWindow::mousePressEvent
 * @param event
 */

void DisplayWindow::mousePressEvent(QMouseEvent *event) {
    mouseXStartPosition = event->x();
    mouseYStartPosition = event->y();
}

/** Method that implements the mouse moved event.
 * @brief DisplayWindow::mouseMoveEvent
 * @param event
 */

void DisplayWindow::mouseMoveEvent(QMouseEvent *event) {
    moveCamera(event);
}

/** Method that implements the move of the camera.
 * @brief DisplayWindow::moveCamera
 * @param event
 */

void DisplayWindow::moveCamera(QMouseEvent *event) {
    makeCurrent();
    glMatrixMode(GL_MODELVIEW);
    int zAngle = 0;
    int yAngle = 0;
    zAngle = (event->x() - mouseXStartPosition) / 4;
    yAngle = (mouseYStartPosition - event->y()) / 8;
    glRotatef(-yAngle, 0, 1, 0);
    glRotatef(yAngle, 1, 0, 0);

    glRotatef(zAngle, 0, 0, 1);
    mouseXStartPosition = event->x();
    mouseYStartPosition = event->y();
    update();
}

/** Method that implements the reset of the camera.
 * @brief DisplayWindow::resetCamera
 */

void DisplayWindow::resetCamera() {
    makeCurrent();
    setModelView();
    update();
}

