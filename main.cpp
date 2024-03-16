#include <QApplication>
#include <QStackedWidget> // Include QStackedWidget for managing multiple pages
#include "mainwindow.h"
#include "welcomepage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    welcomepage welcomePage;

    welcomePage.show();

    return app.exec();
}

