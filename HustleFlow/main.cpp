#include "contentview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ContentView contentView;
    contentView.show();
    return a.exec();
}

