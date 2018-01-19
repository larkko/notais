#include <QApplication>
#include "gui/mainwindow.hh"

int main(int argc, char ** argv)
{
    QApplication application(argc, argv);
    Main_window main_window;
    main_window.show();
    return application.exec();
}






