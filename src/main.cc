#include <QApplication>
#include "gui/mainwindow.hh"
#include "gui/style.hh"

int main(int argc, char ** argv)
{
    QApplication application(argc, argv);
    application.setStyle(get_application_style());
    application.setPalette(get_application_palette());
    Main_window main_window;
    main_window.show();
    return application.exec();
}






