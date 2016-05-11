#include "displaywindow.h"
#include "marker.h"
#include <iostream>

/** Constructor to initialize the window.
 * @brief DisplayWindow::DisplayWindow
 * @param parent
 */

DisplayWindow::DisplayWindow(QWidget *parent) : QOpenGLWidget(parent) {
    firstMarkerPickedIndex = -1;
    secondMarkerPickedIndex = -1;
}

int DisplayWindow::getFirstMarkerPickedIndex() const {
    return firstMarkerPickedIndex;
}

int DisplayWindow::getSecondMarkerPickedIndex() const {
    return secondMarkerPickedIndex;
}

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
    view.lookAt(QVector3D(2, -2, 0.5), QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 0.0, 1.0));
    float * tab = view.data();
    glMultMatrixf(tab);
}

/** Method that sets the
 * @brief DisplayWindow::setCoordinates
 * @param newCoordinates
 */

void DisplayWindow::setCoordinates(const QVector<Marker>& newCoordinates) {
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
    glClearColor(0.0, 0.0 ,0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(3.0);
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    for(int i = 0 ; i < coordinates.size() ; i++) {
        if(i == firstMarkerPickedIndex) {
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(coordinates.at(i).getX() / 1500, coordinates.at(i).getY() / 1500, coordinates.at(i).getZ() / 1500);
            glColor3f(1.0, 1.0, 1.0);
        }
        else if(i == secondMarkerPickedIndex) {
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(coordinates.at(i).getX() / 1500, coordinates.at(i).getY() / 1500, coordinates.at(i).getZ() / 1500);
            glColor3f(1.0, 1.0, 1.0);
        }
        else {
            glVertex3f(coordinates.at(i).getX() / 1500, coordinates.at(i).getY() / 1500, coordinates.at(i).getZ() / 1500);
        }
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
    if(event->modifiers() == Qt::CTRL) {
        pickMarker(event);
    }
}

/** Method that implements the mouse moved event.
 * @brief DisplayWindow::mouseMoveEvent
 * @param event
 */

void DisplayWindow::mouseMoveEvent(QMouseEvent *event) {
    moveCamera(event);
}

void DisplayWindow::pickMarker(QMouseEvent *event) {
    makeCurrent();
    unsigned char pixelRead[4];
    glDrawBuffer(GL_BACK);
    glClearColor(0.0, 0.0 ,0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    for(auto marker : coordinates) {
        glPointSize(3.0);
        glBegin(GL_POINTS);
            glColor3f(marker.getRedId() / 255.0, marker.getGreenId() / 255.0, marker.getBlueId() / 255.0);
            glVertex3f(marker.getX() / 1500, marker.getY() / 1500, marker.getZ() / 1500);
        glEnd();
    }
    glFlush();
    glReadPixels(mouseXStartPosition, height() - mouseYStartPosition, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixelRead);
    int index = (int)pixelRead[0] + (int)pixelRead[1] *256 + (int)pixelRead[2] * 256 *256 - 1;
    if(event->button() == Qt::LeftButton) {
        firstMarkerPickedIndex = index;
    }
    if(event->button() == Qt::RightButton) {
        secondMarkerPickedIndex = index;
    }
    emit markerPicked();

    std::cout << "resultat : " << index <<  std::endl;
    update();
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
