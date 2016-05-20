#include <iostream>
#include "coordinateswindow.h"

CoordinatesWindow::CoordinatesWindow(QWidget *parent) : QWidget(parent)
{
    colorIndex = 7;
    layout = new QGridLayout(this);

    QLabel *headerX = new QLabel("x", this);
    headerX->setAlignment(Qt::AlignCenter);
    QLabel *headerY = new QLabel("y", this);
    headerY->setAlignment(Qt::AlignCenter);
    QLabel *headerZ = new QLabel("z", this);
    headerZ->setAlignment(Qt::AlignCenter);
    QLabel *headerColor = new QLabel("color", this);
    headerColor->setAlignment(Qt::AlignCenter);

    layout->addWidget(headerX, 0, 1);
    layout->addWidget(headerY, 0, 2);
    layout->addWidget(headerZ, 0, 3);
    layout->addWidget(headerColor, 0, 4);
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

void CoordinatesWindow::updateColors(int index) {
    QPalette palette;
    colorIndex = 7 + index;
    std::cout << index << std::endl;
    for(int i = index ; i < xyzVector.size() ; i++) {
        palette.setColor(QPalette::Base, QColor(Qt::GlobalColor(colorIndex)));
        xyzVector.at(i).at(3)->setPalette(palette);
        colorIndex++;
    }
}

