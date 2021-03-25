#include "contentview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ContentView contentView;
    contentView.setFixedSize(800, 600);
    contentView.show();

    return a.exec();
}
