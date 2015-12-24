#include "ECATMain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ECATMain w;
    w.show();

    return a.exec();
}
