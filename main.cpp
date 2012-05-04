#include <QtGui/QApplication>
#include "wkwrap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWkWrap w;

    w.show();

    return a.exec();
}
