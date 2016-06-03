#include "data.h"


/** Constructor to initialize the data.
 * @brief Data::Data
 */

Data::Data() {
    indexCurrentStep = 0;
}

/** Method that displays the data.
 * @brief Data::displayData
 */

void Data::displayData() const {
    for(auto vect : dataCoordinates) {
        for(int i = 0 ; i < vect.size() ; i++) {
            std::cout << vect.at(i).getX() << " " << vect.at(i).getY() << " " << vect.at(i).getZ() << " " << std::flush;
        }
        std::cout << std::endl;
    }
}

/** Method that open the file to read the coordinates contained in every line of the file and stores it.
 * @brief Data::loadData
 * @param fileName
 */

void Data::loadData(QString& fileName) {
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly);
    QString s;
    QStringList liste;
    while(!fichier.atEnd()) {
        dataCoordinates.append(QVector<Marker>());
        s = fichier.readLine(10000);
        liste = s.split('\t');
        for(int i = 0 ; i < liste.size() - 1; i += 3) {
           dataCoordinates.last().append(Marker(i / 3 + 1, liste.at(i).toFloat(), liste.at(i + 1).toFloat(), liste.at(i + 2).toFloat()));
        }
    }
    fichier.close();
}

const QVector<QVector<Marker>>* Data::getDataCoordinates() {
    return &dataCoordinates;
}

/** Method that returns a QVector of a point contained in the storing data.
 * @brief Data::get1Vector
 * @param index
 * @return
 */

const QVector<Marker>& Data::get1Vector(int index) const {
    return dataCoordinates.at(index);
}

const Marker& Data::get1Marker(int step, int index) const {
    return dataCoordinates.at(step).at(index);
}

/** Method that returns the size of the storing data.
 * @brief Data::getDataCoordinatesSize
 * @return
 */

int Data::getDataCoordinatesSize() const {
    return dataCoordinates.size();
}

void Data::swapMarkersData(const std::array<int, 2>& markersIndexes, int step) {
    Marker temp(markersIndexes[1] + 1, dataCoordinates[step][markersIndexes.at(0)]);
    dataCoordinates[step][markersIndexes.at(0)] = Marker(markersIndexes[0] + 1, dataCoordinates[step][markersIndexes.at(1)]);
    dataCoordinates[step][markersIndexes.at(1)] = temp;
}

