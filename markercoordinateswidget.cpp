#include "markercoordinateswidget.h"
#include <iostream>

MarkerCoordinatesWidget::MarkerCoordinatesWidget(int number, int color, QWidget *parent) : QFrame(parent)
{
    markerNumber = new QLabel("Marker n°" + QString::number(number + 1), this);
    x = new QLabel("x = ", this);
    y = new QLabel("y = ", this);
    z = new QLabel("z = ", this);
    x->setMinimumWidth(60);
    x->setAlignment(Qt::AlignCenter);
    y->setMinimumWidth(60);
    y->setAlignment(Qt::AlignCenter);
    z->setMinimumWidth(60);
    z->setAlignment(Qt::AlignCenter);
    markerColor = new QLineEdit("", this);
    markerColor->setReadOnly(true);
    QPalette palette;
    palette.setColor(QPalette::Base, QColor(Qt::GlobalColor(color)));
    markerColor->setPalette(palette);
    layout = new QGridLayout(this);
    layout->setSpacing(0);
    setLayout(layout);
    layout->addWidget(markerNumber, 0, 0);
    layout->addWidget(markerColor, 1, 0);
    layout->addWidget(x, 0, 1);
    layout->addWidget(y, 1, 1);
    layout->addWidget(z, 2, 1);
}

MarkerCoordinatesWidget::~MarkerCoordinatesWidget() {
    //risque de bug
    delete markerColor;
    delete markerNumber;
    delete x;
    delete y;
    delete z;
    for(auto row : coordinatesColumns) {
        for(auto column : row) {
            delete column;
        }
    }
    delete layout;
}

void MarkerCoordinatesWidget::eraseCoordinates(int step) {
    coordinatesColumns[0][step]->setText("");
    coordinatesColumns[1][step]->setText("");
    coordinatesColumns[2][step]->setText("");
}

void MarkerCoordinatesWidget::setStepCoordinates(int step, const Marker& marker) {
    coordinatesColumns[0][step]->setText(QString::number(marker.getX()));
    coordinatesColumns[1][step]->setText(QString::number(marker.getY()));
    coordinatesColumns[2][step]->setText(QString::number(marker.getZ()));
}

void MarkerCoordinatesWidget::addStepCoordinates() {
    for(int i = 0 ; i < 3 ; i++) {
        coordinatesColumns[i].append(new QLineEdit(this));
        coordinatesColumns[i].last()->setReadOnly(true);
        layout->addWidget(coordinatesColumns.at(i).last(), i, coordinatesColumns.at(i).size() + 1);
        //.at(coordinatesColumns.at(i).size() - 1)
    }
    /*for(auto row : coordinatesColumns) {
        row.append(new QLineEdit(this));
        layout->addWidget(row.last(),);
    }*/
    //setStepCoordinates(coordinatesColumns.size() - 1, marker);
}

void MarkerCoordinatesWidget::removeStepCoordinates() {
    for(auto& row : coordinatesColumns) {
        layout->removeWidget(row.last());
        delete row.last();
        row.remove(row.size() - 1);
    }
}

int MarkerCoordinatesWidget::getSizeSteps() {
    return coordinatesColumns[0].size();
}


