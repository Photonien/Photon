#include "MainWindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    Photon::MainWindow window;
    window.show();

    return app.exec();
}
