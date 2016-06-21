#include "displaywindow.h"
#include "programwindow.h"
#include "coordinateswindow.h"
#include "filewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString s("files/comb_traj_20160219_121123.dat");
    ProgramWindow window(s);
    return a.exec();
}
