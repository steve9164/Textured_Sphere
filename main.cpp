#include "dialog.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set OpenGL version to 3.3
//    QSurfaceFormat format;
//    format.setVersion(3, 3);
//    format.setProfile(QSurfaceFormat::CoreProfile);
//    format.setOption(QSurfaceFormat::DebugContext);
//    QSurfaceFormat::setDefaultFormat(format);

    Dialog w;
    w.show();

    return a.exec();
}
