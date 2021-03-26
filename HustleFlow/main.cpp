#include "contentview.h"

#include <QApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ContentView contentView;
    contentView.setFixedSize(1200, 800);
    contentView.show();

//    // if in mainwindow. make sure m_manager lives in .h as member. else it wont work. ( death by scope)
//     QNetworkAccessManager m_manager;

//     // REQUEST
//     QNetworkRequest request = QNetworkRequest(QUrl(""));
//     QNetworkReply* reply = m_manager.get(request);

//     // connect to signal  when its done using lambda)
//     QObject::connect(reply, &QNetworkReply::finished, [reply]() {

//         // read data
//         QString ReplyText = reply->readAll();

//         // qDebug() << ReplyText;
//         // ask doc to parse it
//         QJsonDocument doc = QJsonDocument::fromJson(ReplyText.toUtf8());

//         // we know first element in file is object, to try to ask for such
//         QJsonObject obj = doc.object();

//         // ask object for value
//         QJsonValue value = obj.value(QString("bid_1"));
//         qDebug() << "Bid value is" << value.toString();

//         reply->deleteLater();
//     });

     return a.exec();
}

