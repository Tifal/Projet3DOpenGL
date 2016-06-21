#include "data.h"

Data::Data() {}

void Data::displayData() const {
    for(auto vect : dataCoordinates) {
        for(int i = 0 ; i < vect.size() ; i++) {
            std::cout << vect.at(i).getX() << " " << vect.at(i).getY() << " " << vect.at(i).getZ() << " " << std::flush;
        }
        std::cout << std::endl;
    }
}

void Data::loadData(QString& fileName) {
    dataCoordinates =   QVector<QVector<Marker>>();
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly);
    QString s;
    QStringList liste;
    while(!fichier.atEnd()) {
        dataCoordinates.append(QVector<Marker>());
        s = fichier.readLine(10000);
        liste = s.split('\t');
        for(int i = 0 ; i < liste.size() - 1; i += 3) {
         // please refer to the comment in the pickMarker method of DisplayWindow to understand why 1 is added to the identifier of the
         // Marker constructor
           dataCoordinates.last().append(Marker(i / 3 + 1, liste.at(i).toFloat(), liste.at(i + 1).toFloat(), liste.at(i + 2).toFloat()));
        }
    }
    fichier.close();
}

void Data::saveData(QString& fileName) {
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    for(auto line : dataCoordinates) {
        for(auto cell : line) {
            out << cell.getX() << "\t" << cell.getY() << "\t" << cell.getZ() << "\t";
        }
        out << "\n";
    }
}

void Data::saveData() {
    QString fileName = QFileDialog::getSaveFileName();
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    for(auto line : dataCoordinates) {
        for(auto cell : line) {
            out << cell.getX() << "\t" << cell.getY() << "\t" << cell.getZ() << "\t";
        }
        out << "\n";
    }
}

void Data::saveDataSkeleton(const QVector<std::array<int, 2>>& linkedMarkersIndexes) {
    QString fileName = QFileDialog::getSaveFileName();
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    for(int i = 0 ; i < linkedMarkersIndexes.size() ; i++) {
        out << linkedMarkersIndexes.at(i).at(0) << "\t" << linkedMarkersIndexes.at(i).at(1) << "\t";
        out << "\n";
    }
}

const QVector<QVector<Marker>>* Data::getDataCoordinates() const {
    return &dataCoordinates;
}

const QVector<Marker>& Data::get1Vector(int index) const {
    return dataCoordinates.at(index);
}

const Marker& Data::get1Marker(int step, int index) const {
    return dataCoordinates.at(step).at(index);
}

int Data::getDataCoordinatesSize() const {
    return dataCoordinates.size();
}

void Data::swapMarkersData(const std::array<int, 2>& markersIndexes, int step) {
    // the first parameter of the constructor is an index which is used to compute the color identifier of the marker
    Marker temp(markersIndexes[1] + 1, dataCoordinates[step][markersIndexes.at(0)]);
    // please refer to the comment in the pickMarker method of DisplayWindow to understand why 1 is added to the identifier
    // of the Marker constructor
    dataCoordinates[step][markersIndexes.at(0)] = Marker(markersIndexes[0] + 1, dataCoordinates[step][markersIndexes.at(1)]);
    dataCoordinates[step][markersIndexes.at(1)] = temp;
}

