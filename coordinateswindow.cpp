#include <iostream>
#include "coordinateswindow.h"

CoordinatesWindow::CoordinatesWindow(QWidget *parent) : QWidget(parent)
{
    colorIndex = 7;
    layout = new QGridLayout(this);
    setWindowTitle("marker coordinates window");

    //QLabel *subtitleDistance = new QLabel("distance between markers", this);
    //subtitleDistance->setMinimumHeight(50);
    //distanceMarker1 = new QComboBox(this);
    //distanceMarker2 = new QComboBox(this);

    QLabel *subTitleCoordinates = new QLabel("marker coordinates", this);
    subTitleCoordinates->setMinimumHeight(50);
    QLabel *headerX = new QLabel("x", this);
    QLabel *headerY = new QLabel("y", this);
    QLabel *headerZ = new QLabel("z", this);
    QLabel *headerColor = new QLabel("color", this);

    //layout->addWidget(subtitleDistance, 0, 0, 1, 6, Qt::AlignCenter);
    //layout->addWidget(distanceMarker1, 1, 0, 1, 3);
    //layout->addWidget(distanceMarker2, 1, 3, 1, 3);
    layout->addWidget(subTitleCoordinates, 2, 0, 1, 6, Qt::AlignCenter);
    layout->addWidget(headerX, 3, 1, Qt::AlignCenter);
    layout->addWidget(headerY, 3, 2, Qt::AlignCenter);
    layout->addWidget(headerZ, 3, 3, Qt::AlignCenter);
    layout->addWidget(headerColor, 3, 4, Qt::AlignCenter);
    layout->setSpacing(0.0);

    this->setLayout(layout);
}

/*void CoordinatesWindow::setDistance(const Marker& marker1, const Marker& marker2) {
    float result = pow((marker2.getX() - marker1.getX()), 2) + pow((marker2.getY() - marker1.getY()), 2) + pow((marker2.getZ() - marker1.getZ()), 2);
    result = sqrt(result);
    distance->setText(QString::number(result));
}*/

void CoordinatesWindow::addLineCoordinates(const Marker& marker, int color) {
    int row = layout->rowCount();
    xyzVector.append(QVector<QLineEdit*>());
    QPalette palette;
    labelVector.append(new QLabel("selected marker number " + QString::number(xyzVector.size()), this));
    labelVector.last()->setMinimumWidth(140);
    layout->addWidget(labelVector.last(), row, 0);
    for(int i = 1 ; i < 5 ; i++) {
        xyzVector.last().append(new QLineEdit(this));
        xyzVector.last().last()->setReadOnly(true);
        layout->addWidget(xyzVector.last().last(), row, i);
    }
    xyzVector.last().at(0)->setText(QString::number(marker.getX()));
    xyzVector.last().at(1)->setText(QString::number(marker.getY()));
    xyzVector.last().at(2)->setText(QString::number(marker.getZ()));
    palette.setColor(QPalette::Base, QColor(Qt::GlobalColor(color)));
    xyzVector.last().at(3)->setPalette(palette);
    //colorIndex++;
    buttonVector.append(new QPushButton("remove", this));
    connect(buttonVector.last(), SIGNAL(clicked(bool)), this, SLOT(removeLineCoordinates()));
    layout->addWidget(buttonVector.last(), row, 5);
}

void CoordinatesWindow::updateCoordinates(QVector<Marker>& markerVector) {
    int i = 0;
    for(auto row : xyzVector) {
        row.at(0)->setText(QString::number(markerVector.at(i).getX()));
        row.at(1)->setText(QString::number(markerVector.at(i).getY()));
        row.at(2)->setText(QString::number(markerVector.at(i).getZ()));
        i++;
    }
}

void CoordinatesWindow::removeLineCoordinates() {
    int i = 0;
    while(sender() != (QObject*)buttonVector.at(i)) {
        i++;
    }
    emit lineRemoved(i);
    layout->removeWidget(labelVector.at(i));
    delete labelVector.at(i);
    labelVector.remove(i);
    updateLabelNumber(i);
    for(auto textField : xyzVector.at(i)) {
        layout->removeWidget(textField);
        delete textField;
    }
    xyzVector.remove(i);
    layout->removeWidget(buttonVector.at(i));
    delete buttonVector.at(i);
    buttonVector.remove(i);
    //updateColors(i);
}

void CoordinatesWindow::updateLabelNumber(int index) {
    while(index < labelVector.size()) {
        labelVector.at(index)->setText("selected marker number " + QString::number(index + 1));
        index++;
    }
}

void CoordinatesWindow::swapCoordinates(const std::array<int, 2>& markersToBeSwaped) {
    std::array<QString, 3> temp({xyzVector.at(markersToBeSwaped.at(0)).at(0)->text(), xyzVector.at(markersToBeSwaped.at(0)).at(1)->text(),
                                xyzVector.at(markersToBeSwaped.at(0)).at(2)->text()});
    for(int i = 0 ; i < 3 ; i++) {
        xyzVector.at(markersToBeSwaped.at(0)).at(i)->setText(xyzVector.at(markersToBeSwaped.at(1)).at(i)->text());
        xyzVector.at(markersToBeSwaped.at(1)).at(i)->setText(temp.at(i));
    }

}

/*void CoordinatesWindow::updateColors(int index) {
    QPalette palette;
    colorIndex = 7 + index;
    std::cout << index << std::endl;
    for(int i = index ; i < xyzVector.size() ; i++) {
        palette.setColor(QPalette::Base, QColor(Qt::GlobalColor(colorIndex)));
        xyzVector.at(i).at(3)->setPalette(palette);
        colorIndex++;
    }
}*/

