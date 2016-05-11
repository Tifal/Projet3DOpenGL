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

/** Method that returns a QVector of a point contained in the storing data.
 * @brief Data::get1Vector
 * @param index
 * @return
 */

const QVector<Marker>& Data::get1Vector(int index) {
    return dataCoordinates.at(index);
}

/** Method that returns the size of the storing data.
 * @brief Data::getDataCoordinatesSize
 * @return
 */

int Data::getDataCoordinatesSize() const {
    return dataCoordinates.size();
}
