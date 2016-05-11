#include "displaywindow.h"
#include "programwindow.h"
#include "coordinateswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProgramWindow window;

    //window.show();

    window.configureScreen();

    return a.exec();
}
