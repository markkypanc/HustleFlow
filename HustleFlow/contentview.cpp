#include "contentview.h"
#include "ui_contentview.h"
#include "constants.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkReply>

#include <string>
using namespace std;


ContentView::ContentView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContentView)
{
    ui->setupUi(this);
    connect(&manager, &QNetworkAccessManager::finished, this, &ContentView::onManagerFinished);
}

ContentView::~ContentView()
{
    delete ui;
}


void ContentView::on_pushButton_clicked()
{
    QNetworkRequest request(QUrl("http://hapi.fhir.org/baseDstu3/Patient/4705560"));
        request.setRawHeader("Content-Type", "application/fhir+json");
        QFile file("/path/of/themostsimplepatientJSON.json");
        if(file.open(QIODevice::ReadOnly)){
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            QJsonObject obj = doc.object();
            obj["id"] = "4705560"; // add ID
            doc.setObject(obj);
            manager.put(request, doc.toJson());
        }
}

void ContentView::onManagerFinished(QNetworkReply *reply) {
    qDebug() << reply->readAll();
}

