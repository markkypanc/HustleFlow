#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ContentView; }
QT_END_NAMESPACE

class QPushButton;
class ContentView : public QMainWindow
{
    Q_OBJECT

public:
    ContentView(QWidget *parent = nullptr);
    ~ContentView();

private:
    Ui::ContentView *ui;
    QPushButton *button;
};
#endif // CONTENTVIEW_H
