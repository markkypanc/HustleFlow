#include "contentview.h"
#include "ui_contentview.h"
#include <QPushButton>

ContentView::ContentView(QWidget *parent): QMainWindow(parent), ui(new Ui::ContentView) {
    ui->setupUi(this);

    button = new QPushButton("Click me", this);
    button->setFixedSize(200, 56);

    int screenWidth = geometry().width();
    int screenHeight = geometry().height();
    int buttonWidth = button->width();
    int buttonHeight = button->height();

    button->setGeometry(screenWidth/2 - buttonWidth/2, screenHeight/2 - buttonHeight/2, buttonWidth, buttonHeight);
}

ContentView::~ContentView()
{
    delete ui;
}

