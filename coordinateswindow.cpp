#include "coordinateswindow.h"

CoordinatesWindow::CoordinatesWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(300,300);

    layout = new QGridLayout(this);

    x1 = new QLineEdit(this);
    y1 = new QLineEdit(this);
    z1 = new QLineEdit(this);
    x2 = new QLineEdit(this);
    y2 = new QLineEdit(this);
    z2 = new QLineEdit(this);
    distance = new QLineEdit(this);

    x1->setReadOnly(true);
    y1->setReadOnly(true);
    z1->setReadOnly(true);
    x2->setReadOnly(true);
    y2->setReadOnly(true);
    z2->setReadOnly(true);
    distance->setReadOnly(true);

    QLabel *labelX1 = new QLabel("x = ", this);
    QLabel *labelY1 = new QLabel("y = ", this);
    QLabel *labelZ1 = new QLabel("z = ", this);

    QLabel *subtitleMarker1 = new QLabel("Coordinates picked marker 1 :", this);
    layout->addWidget(subtitleMarker1, 0, 0, 1, 2);
    layout->addWidget(labelX1, 1, 0);
    layout->addWidget(x1, 1, 1);
    layout->addWidget(labelY1, 2, 0);
    layout->addWidget(y1, 2, 1);
    layout->addWidget(labelZ1, 3, 0);
    layout->addWidget(z1, 3, 1);

    QLabel *labelX2 = new QLabel("x = ", this);
    QLabel *labelY2 = new QLabel("y = ", this);
    QLabel *labelZ2 = new QLabel("z = ", this);


    QLabel *subtitleMarker2 = new QLabel("Coordinates picked marker 2 :", this);
    layout->addWidget(subtitleMarker2, 4, 0, 1, 2);
    layout->addWidget(labelX2, 5, 0);
    layout->addWidget(x2, 5, 1);
    layout->addWidget(labelY2,6, 0);
    layout->addWidget(y2, 6, 1);
    layout->addWidget(labelZ2, 7, 0);
    layout->addWidget(z2, 7, 1);

    QLabel *subtitleDistance = new QLabel("Distance between the markers :", this);
    QLabel *labelDistance = new QLabel("distance = ", this);
    layout->addWidget(subtitleDistance, 8, 0, 1, 2);
    layout->addWidget(labelDistance, 9, 0);
    layout->addWidget(distance, 9, 1);

    this->setLayout(layout);
}

void CoordinatesWindow::resetCoordinatesMarker1() {
    x1->setText("");
    y1->setText("");
    z1->setText("");
    distance->setText("");
}

void CoordinatesWindow::resetCoordinatesMarker2() {
    x2->setText("");
    y2->setText("");
    z2->setText("");
    distance->setText("");
}

void CoordinatesWindow::setCoordinatesMarker1(const Marker& marker) {
    x1->setText(QString::number(marker.getX()));
    y1->setText(QString::number(marker.getY()));
    z1->setText(QString::number(marker.getZ()));
}

void CoordinatesWindow::setCoordinatesMarker2(const Marker& marker) {
    x2->setText(QString::number(marker.getX()));
    y2->setText(QString::number(marker.getY()));
    z2->setText(QString::number(marker.getZ()));
}

void CoordinatesWindow::setDistance(const Marker& marker1, const Marker& marker2) {
    float result = pow((marker2.getX() - marker1.getX()), 2) + pow((marker2.getY() - marker1.getY()), 2) + pow((marker2.getZ() - marker1.getZ()), 2);
    result = sqrt(result);
    distance->setText(QString::number(result));
}

