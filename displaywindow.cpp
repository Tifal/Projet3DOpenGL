#include "displaywindow.h"
//#include "marker.h"
#include <iostream>


/** Constructor to initialize the window.
 * @brief DisplayWindow::DisplayWindow
 * @param parent
 */

DisplayWindow::DisplayWindow(QWidget *parent) : QOpenGLWidget(parent) {
    data = NULL;
    currentStep = 0;
    linkMarkerMode = false;
    selectMarkerMode = false;
   // swapMode = true;
    displayFormerSteps = false;
    displayFurtherSteps = false;
    formerStepsPoints = false;
    lineBeingDrawn = false;
    linkedMarkersIndexes.append(std::array<int, 2>({-1, -1}));
    for(auto& element : markersToBeSwapedIndexes) {
        element = -1;
    }
    for(int i = 7 ; i < 19 ; i++) {
        colorsAvailable.append(i);
    }
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

void DisplayWindow::setData(const QVector<QVector<Marker>> * pointerToData) {
    data = pointerToData;
}

void DisplayWindow::setCurrentStep(int index) {
    currentStep = index;
}

const QVector<int>& DisplayWindow::getSelectedMarkerIndexes() const {
    return selectedMarkerIndexes;
}

const std::array<int, 2>& DisplayWindow::getMarkersToBeSwaped() const {
    return markersToBeSwapedIndexes;
}

void DisplayWindow::removePickedIndex(int index) {
    selectedMarkerIndexes.remove(index);
    colorsAvailable.append(colorsAvailable.at(index));
    colorsAvailable.remove(index);
    update();
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
    glPointSize(3.0);
    glClearColor(0.0, 0.0 ,0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    paintMarkers();
    if(lineBeingDrawn) {
        paintMarkerWithCross();
    }
    paintLinkedMarkers();
    paintSelectedMarkers();
    if(displayFormerSteps) {
        paintFormerSteps();
    }
    if(displayFurtherSteps) {
        paintFurtherSteps();
    }
    paintMarkersWithRedCross();
    paintAxes();
    glFlush();
}

void DisplayWindow::paintMarkers() {
    makeCurrent();
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    for(auto marker : data->at(currentStep)) {
        glVertex3f(marker.getX() / 1500, marker.getY() / 1500, marker.getZ() / 1500);
    }
    glEnd();
}

void DisplayWindow::paintSelectedMarkers() {
    makeCurrent();
    int colorIndex = 0;
    QColor *color;
    glBegin(GL_POINTS);
    for(auto index : selectedMarkerIndexes) {
        color = new QColor(Qt::GlobalColor(colorsAvailable.at(colorIndex)));
        glColor3f(color->red() / 255.0, color->green() / 255.0, color->blue() / 255.0);
        glVertex3f(data->at(currentStep).at(index).getX() / 1500, data->at(currentStep).at(index).getY() / 1500, data->at(currentStep).at(index).getZ() / 1500);
        delete color;
        colorIndex++;
    }
    glColor3f(1.0, 1.0, 1.0);
    glEnd();
}

void DisplayWindow::paintAxes() {
    makeCurrent();
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
}

void DisplayWindow::paintMarkerWithCross() {
    makeCurrent();
    glBegin(GL_LINES);
        glVertex3f((getMarkerWithCross().getX() + 50) / 1500, (getMarkerWithCross().getY()) / 1500, (getMarkerWithCross().getZ()) / 1500);
        glVertex3f((getMarkerWithCross().getX() - 50) / 1500, (getMarkerWithCross().getY()) / 1500, (getMarkerWithCross().getZ()) / 1500);
        glVertex3f((getMarkerWithCross().getX()) / 1500, (getMarkerWithCross().getY() + 50) / 1500, (getMarkerWithCross().getZ()) / 1500);
        glVertex3f((getMarkerWithCross().getX()) / 1500, (getMarkerWithCross().getY() - 50) / 1500, (getMarkerWithCross().getZ()) / 1500);
        glVertex3f((getMarkerWithCross().getX()) / 1500, (getMarkerWithCross().getY()) / 1500, (getMarkerWithCross().getZ() + 50) / 1500);
        glVertex3f((getMarkerWithCross().getX()) / 1500, (getMarkerWithCross().getY()) / 1500, (getMarkerWithCross().getZ() - 50) / 1500);
    glEnd();
}

void DisplayWindow::paintMarkersWithRedCross() {
    makeCurrent();
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    for(auto index : markersToBeSwapedIndexes) {
        if(index != -1) {
            glVertex3f((data->at(currentStep).at(index).getX() + 50) /1500, data->at(currentStep).at(index).getY() / 1500, data->at(currentStep).at(index).getZ()/ 1500);
            glVertex3f((data->at(currentStep).at(index).getX() - 50) /1500, data->at(currentStep).at(index).getY() / 1500, data->at(currentStep).at(index).getZ()/ 1500);
            glVertex3f(data->at(currentStep).at(index).getX() /1500, (data->at(currentStep).at(index).getY() + 50) / 1500, data->at(currentStep).at(index).getZ()/ 1500);
            glVertex3f(data->at(currentStep).at(index).getX() /1500, (data->at(currentStep).at(index).getY() - 50) / 1500, data->at(currentStep).at(index).getZ()/ 1500);
            glVertex3f(data->at(currentStep).at(index).getX() / 1500, data->at(currentStep).at(index).getY() / 1500, (data->at(currentStep).at(index).getZ() + 50) / 1500);
            glVertex3f(data->at(currentStep).at(index).getX() / 1500, data->at(currentStep).at(index).getY() / 1500, (data->at(currentStep).at(index).getZ() - 50) / 1500);
        }
    }
    glEnd();
}

void DisplayWindow::paintFormerSteps() {
    makeCurrent();
    glPointSize(1.5);
    int j = 0;
    int colorIndex = 0;
    QColor *color;
    for(int i = 0 ; i < data->last().size() ; i++) {
        if(currentStep >= numberOfFormerStepsDisplayed) {
            j = currentStep - numberOfFormerStepsDisplayed;
        }
        else {
            j = 0;
        }
        if(formerStepsPoints) {
            glBegin(GL_POINTS);
        }
        else {
            glBegin(GL_LINE_STRIP);
        }
        colorIndex = selectedMarkerIndexes.indexOf(i);
        if(colorIndex != -1) {
            color = new QColor(Qt::GlobalColor(colorsAvailable.at(colorIndex)));
            glColor3f(color->red() / 255.0, color->green() / 255.0, color->blue() / 255.0);
            delete color;
            colorIndex++;
            while(j <= currentStep) {
                glVertex3f(data->at(j).at(i).getX() / 1500, data->at(j).at(i).getY() / 1500, data->at(j).at(i).getZ() / 1500);
                j++;
            }
            glColor3f(1.0, 1.0, 1.0);
        }
        else{
            while(j <= currentStep) {
                glVertex3f(data->at(j).at(i).getX() / 1500, data->at(j).at(i).getY() / 1500, data->at(j).at(i).getZ() / 1500);
                j++;
            }
        }
        glEnd();
    }
}

void DisplayWindow::paintFurtherSteps() {
    makeCurrent();
    glPointSize(1.5);
    int colorIndex = 0;
    int indexSelected = 0;
    QColor *color;
    int j = 0;
    int limitOfStepsDisplayed = currentStep + numberOfFurtherStepsDisplayed;
    if(data->size() < limitOfStepsDisplayed) {
        limitOfStepsDisplayed = data->size();
    }
    for(int i = 0; i < selectedMarkerIndexes.size() ; i++) {
        indexSelected = selectedMarkerIndexes.at(i);
        j = currentStep;
        color = new QColor(Qt::GlobalColor(colorsAvailable.at(colorIndex)));
        glBegin(GL_LINE_STRIP);
        glColor3f(color->red() / 255.0, color->green() / 255.0, color->blue() / 255.0);
        delete color;
        colorIndex++;
        //rajouter = ?
        while(j < limitOfStepsDisplayed) {
            glVertex3f(data->at(j).at(indexSelected).getX() / 1500, data->at(j).at(indexSelected).getY() / 1500, data->at(j).at(indexSelected).getZ() / 1500);
            j++;
        }
        glEnd();
    }
}

void DisplayWindow::paintLinkedMarkers() {
    makeCurrent();
    glBegin(GL_LINES);
        for(int i = 0 ; i < linkedMarkersIndexes.size() - 1 ; i++) {
            glVertex3f(data->at(currentStep).at(linkedMarkersIndexes.at(i)[0]).getX() / 1500, data->at(currentStep).at(linkedMarkersIndexes.at(i)[0]).getY() / 1500,
                    data->at(currentStep).at(linkedMarkersIndexes.at(i)[0]).getZ() / 1500);
            glVertex3f(data->at(currentStep).at(linkedMarkersIndexes.at(i)[1]).getX() / 1500, data->at(currentStep).at(linkedMarkersIndexes.at(i)[1]).getY() / 1500,
                    data->at(currentStep).at(linkedMarkersIndexes.at(i)[1]).getZ() / 1500);
        }
    glEnd();
}

const Marker& DisplayWindow::getMarkerWithCross() const {
    return data->at(currentStep).at(linkedMarkersIndexes.last()[0]);
}

/** Method that implements the mouse pressed event.
 * @brief DisplayWindow::mousePressEvent
 * @param event
 */

void DisplayWindow::mousePressEvent(QMouseEvent *event) {
    mouseXStartPosition = event->x();
    mouseYStartPosition = event->y();
    if(selectMarkerMode) {
        selectMarker();
    }
    else if(linkMarkerMode) {
        linkMarkerLine();
    }
    else if(swapMode) {
        swapMarkers();
    }
}

/** Method that implements the mouse moved event.
 * @brief DisplayWindow::mouseMoveEvent
 * @param event
 */

void DisplayWindow::mouseMoveEvent(QMouseEvent *event) {
    moveCamera(event);
}

int DisplayWindow::pickMarker() {
    makeCurrent();
    unsigned char pixelRead[3];
    glDrawBuffer(GL_BACK);
    glClearColor(0.0, 0.0 ,0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    for(auto marker : data->at(currentStep)) {
        glPointSize(3.0);
        glBegin(GL_POINTS);
            glColor3f(marker.getRedId() / 255.0, marker.getGreenId() / 255.0, marker.getBlueId() / 255.0);
            glVertex3f(marker.getX() / 1500, marker.getY() / 1500, marker.getZ() / 1500);
        glEnd();
    }
    glFlush();
    glReadPixels(mouseXStartPosition, height() - mouseYStartPosition, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixelRead);
    update();
    return (int)pixelRead[0] + (int)pixelRead[1] *256 + (int)pixelRead[2] * 256 *256 - 1;
}

void DisplayWindow::selectMarker() {
    int index = pickMarker();
    if(selectedMarkerIndexes.size() < 12 && index != -1 && selectedMarkerIndexes.indexOf(index) == -1) {
        selectedMarkerIndexes.append(index);
        emit markerPicked(index, colorsAvailable.at(selectedMarkerIndexes.size() - 1));
    }
    update();
}

/*void DisplayWindow::linkMarkerLine() {
    int index = pickMarker();
    if(index == -1 || index == linkedMarkersIndexes.last()[0]) {
        linkedMarkersIndexes.last()[0] = -1;
        lineBeingDrawn = false;
    }
    else {
        if(linkedMarkersIndexes.last()[0] != -1) {
            linkedMarkersIndexes.last()[1] = index;
            lineBeingDrawn = false;
            linkedMarkersIndexes.append(std::array<int, 2>({-1, -1}));
        }
        else {
            linkedMarkersIndexes.last()[0] = index;
            lineBeingDrawn = true;
        }
    }
    update();
}*/

void DisplayWindow::linkMarkerLine() {
    int index = pickMarker();
    if(index == -1 || index == linkedMarkersIndexes.last()[0]) {
        linkedMarkersIndexes.last()[0] = -1;
        lineBeingDrawn = false;
    }
    else {
        if(linkedMarkersIndexes.last()[0] != -1) {
            linkedMarkersIndexes.last()[1] = index;
            if(alreadyLinkedMarkers(linkedMarkersIndexes.last())) {
                linkedMarkersIndexes.last()[0] = -1;
                linkedMarkersIndexes.last()[1] = -1;
            }
            else {
                linkedMarkersIndexes.append(std::array<int, 2>({-1, -1}));
            }
            lineBeingDrawn = false;
        }
        else {
            linkedMarkersIndexes.last()[0] = index;
            lineBeingDrawn = true;
        }
    }
    for(auto element : linkedMarkersIndexes) {
        std::cout << element[0] << ";" << element[1] << std::endl;
    }
    update();
}

bool DisplayWindow::alreadyLinkedMarkers(std::array<int, 2>& linkedMarkers) {
    for(int i = 0 ; i < linkedMarkersIndexes.size() - 1 ; i++) {
        if((linkedMarkers[0] == linkedMarkersIndexes.at(i)[0] && linkedMarkers[1] == linkedMarkersIndexes.at(i)[1]) ||
            (linkedMarkers[0] == linkedMarkersIndexes.at(i)[1] && linkedMarkers[1] == linkedMarkersIndexes.at(i)[0])) {
            return true;
        }
    }
    return false;
}

void DisplayWindow::resetLinkedMarkersIndexes() {
    linkedMarkersIndexes = QVector<std::array<int, 2>>();
    linkedMarkersIndexes.append(std::array<int, 2>({-1, -1}));
    update();
}

/*void DisplayWindow::swapMarkers() {
    int index = pickMarker();
    if(index == -1 || index == markersToBeSwapedIndexes.at(0)) {
        markersToBeSwapedIndexes.at(0) = -1;
    }
    else {
        if(markersToBeSwapedIndexes.at(0) == -1) {
            markersToBeSwapedIndexes[0] = index;
        }
        else {
            markersToBeSwapedIndexes[1] = index;
        }
    }
    for(auto element : markersToBeSwapedIndexes) {
        std::cout << element << ";" << std::flush;
    }
    std::cout << std::endl;
}*/

void DisplayWindow::swapMarkers() {
    int index = pickMarker();
    if(markersToBeSwapedIndexes.at(0) == -1){
        markersToBeSwapedIndexes.at(0)=index;
    }
    else {
        if(markersToBeSwapedIndexes.at(1) == -1) {
            if(index == markersToBeSwapedIndexes.at(0) || index == -1) {
                markersToBeSwapedIndexes.at(0) = -1;
            }
            else {
                markersToBeSwapedIndexes.at(1) = index;
            }
        }
        else {
            if(index == markersToBeSwapedIndexes.at(1)) {
                markersToBeSwapedIndexes.at(1) = -1;
            }
            else if(index == markersToBeSwapedIndexes.at(0)){
                markersToBeSwapedIndexes.at(0)=markersToBeSwapedIndexes.at(1);
                markersToBeSwapedIndexes.at(1)=-1;

            }
            else {
                markersToBeSwapedIndexes.at(1) = index;
            }
        }
    }
    update();
    for(auto element : markersToBeSwapedIndexes) {
        std::cout << element << ";" << std::flush;
    }
    std::cout << std::endl;
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

void DisplayWindow::setLinkMarkerMode(bool boolean) {
    linkMarkerMode = boolean;
}

void DisplayWindow::setSelectMarkerMode(bool boolean) {
    selectMarkerMode = boolean;
}

void DisplayWindow::setDisplayFormerSteps(bool boolean) {
    displayFormerSteps = boolean;
    update();
}

void DisplayWindow::setNumberOfFormerStepsDisplayed(int number) {
    numberOfFormerStepsDisplayed = number;
    update();
}

void DisplayWindow::setDisplayFurtherSteps(bool boolean) {
    displayFurtherSteps = boolean;
    update();
}

void DisplayWindow::setNumberOfFurtherStepsDisplayed(int number) {
    numberOfFurtherStepsDisplayed = number;
    update();
}

void DisplayWindow::setFormerStepsPoints(bool boolean) {
    formerStepsPoints = boolean;
    update();
}
