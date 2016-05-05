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
        for(auto element : vect) {
            std::cout << element << " " << std::flush;
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

/** Method that returns a QVector of a point contained in the storing data.
 * @brief Data::get1Vector
 * @param index
 * @return
 */

const QVector<float>& Data::get1Vector(int index) {
    if(index < 0 || index >= dataCoordinates.size()) {
        std::cout << "the index must be positive and inferior to the size of the vector" << std::endl;
    }
    else {
        return dataCoordinates.at(index);
    }
}

/** Method that returns the size of the storing data.
 * @brief Data::getDataCoordinatesSize
 * @return
 */

int Data::getDataCoordinatesSize() const {
    return dataCoordinates.size();
}
