#include "memorygame.h"
#include <QApplication>

// a memorygame is created and shown
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    memorygame w;
    w.show();

    return a.exec();
}
