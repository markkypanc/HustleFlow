#include "contentview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ContentView w;
    w.show();
    return a.exec();
}
