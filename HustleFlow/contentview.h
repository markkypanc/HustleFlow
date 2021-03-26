#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

#include <QMainWindow>
#include <QNetworkAccessManager>

namespace Ui {
class ContentView;
}


// MARK: - MAIN CONTENT VIEW
class ContentView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ContentView(QWidget *parent = nullptr);
    ~ContentView();

private slots:
    void on_pushButton_clicked();
    void onManagerFinished(QNetworkReply *reply);

private:
    Ui::ContentView *ui;
    QNetworkAccessManager manager;
};
#endif // CONTENTVIEW_H
