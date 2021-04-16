#ifndef NEWSROWCUSTOMVIEW_H
#define NEWSROWCUSTOMVIEW_H

#include <QWidget>

#include <QUrl>

class NewsRowCustomView : public QWidget
{
    Q_OBJECT
public:
    explicit NewsRowCustomView(int index, const QJsonObject & obj, QWidget *parent = nullptr);
private slots:
    void OnViewClicked();
private:
    QUrl mURL;

signals:

};

#endif // NEWSROWCUSTOMVIEW_H
