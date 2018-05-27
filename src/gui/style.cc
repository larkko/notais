#include "style.hh"

#include <QStyleFactory>

QStyle * get_application_style()
{
    return QStyleFactory::create("fusion");
}

QPalette get_application_palette()
{
    QPalette p;
    p.setColor(QPalette::Window, Qt::darkGray);
    p.setColor(QPalette::WindowText, Qt::white);
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::AlternateBase, Qt::darkBlue);
    p.setColor(QPalette::ToolTipBase, Qt::black);
    p.setColor(QPalette::ToolTipText, Qt::lightGray);
    p.setColor(QPalette::Text, Qt::white);
    p.setColor(QPalette::Button, Qt::darkGray);
    p.setColor(QPalette::ButtonText, Qt::white);
    p.setColor(QPalette::BrightText, Qt::lightGray);
    p.setColor(QPalette::Light, Qt::lightGray);
    p.setColor(QPalette::Midlight, Qt::gray);
    p.setColor(QPalette::Dark, Qt::black);
    p.setColor(QPalette::Mid, Qt::darkGray);
    p.setColor(QPalette::Shadow, Qt::black);
    p.setColor(QPalette::Highlight, Qt::darkCyan);
    p.setColor(QPalette::HighlightedText, Qt::white);
    p.setColor(QPalette::Link, Qt::blue);
    p.setColor(QPalette::LinkVisited, Qt::magenta);
    return p;
}
