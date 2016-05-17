#include "displaywindow.h"
#include "programwindow.h"
#include "coordinateswindow.h"
#include <QApplication>
#include <filewindow.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

        ProgramWindow window;

        //window.show();

        window.configureScreen();

        return a.exec();
   /* QApplication a(argc, argv);

   // ProgramWindow window;

    //window.show();
    FileWindow window;
    window.setViewMrNilsen();
    window.show();
    //window.configureScreen();

    return a.exec();
    */
}
