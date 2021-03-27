#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QWidget>

#include <QUrl>

class NetworkManager : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkManager(int index, const QJsonObject & obj, QWidget *parent = nullptr);
private slots:
    void OnViewClicked();
private:
    QUrl mURL;

signals:

};

#endif // NETWORKMANAGER_H
