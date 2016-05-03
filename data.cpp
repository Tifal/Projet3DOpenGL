#include "data.h"

Data::Data() {
    indexCurrentStep = 0;
}

void Data::displayData() const {
    for(auto vect : dataCoordinates) {
        for(auto element : vect) {
            std::cout << element << " " << std::flush;
        }
        std::cout << std::endl;
    }
}

void Data::loadData(QString& fileName) {
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly);
    QString s;
    QStringList liste;
    while(!fichier.atEnd()) {
        dataCoordinates.append(QVector<float>());
        s = fichier.readLine(10000);
        liste = s.split('\t');
        for(auto element : liste) {
            dataCoordinates.last().append(element.toFloat());
        }
        dataCoordinates.last().removeLast();
    }
    fichier.close();
}

const QVector<float>& Data::get1Vector(int index) {
    if(index < 0 || index >= dataCoordinates.size()) {
        std::cout << "the index must be positive and inferior to the size of the vector" << std::endl;
    }
    else {
        return dataCoordinates.at(index);
    }
}

int Data::getDataCoordinatesSize() const {
    return dataCoordinates.size();
}
