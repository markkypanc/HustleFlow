#include "contentview.h"
#include "ui_contentview.h"

ContentView::ContentView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ContentView)
{
    ui->setupUi(this);
}

ContentView::~ContentView()
{
    delete ui;
}

