#include "newsrowcustomview.h"

// UI
#include <QDesktopServices>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

// API
#include <QJsonObject>

#include <QDebug>

NewsRowCustomView::NewsRowCustomView(int index, const QJsonObject & obj, QWidget *parent) : QWidget(parent)
{
    // NEW URL
    QJsonObject::const_iterator it = obj.constFind("url");

    if(it != obj.constEnd())
        mURL.setUrl(it.value().toString());
    else
        mURL.setUrl(QString("https://news.ycombinator.com/item?id=%1").arg(obj["id"].toInt()));

    // LAYOUT
    QHBoxLayout *layoutView = new QHBoxLayout;
    setLayout(layoutView);

    // ROW VIEW
    QLabel *newsRowView = new QLabel(QString("%1.").arg(index, 2));
    layoutView->addWidget(newsRowView);

    // FONT EXTENSION
    QFont titleFont;
    titleFont.setPointSize(13);
    titleFont.setBold(true);

    newsRowView = new QLabel(obj["title"].toString());
    newsRowView->setFont(titleFont);
    layoutView->addWidget(newsRowView);

    // HOST
    newsRowView = new QLabel(QString("(%1)").arg(mURL.host()));
    layoutView->addWidget(newsRowView);

    // SPACER
    layoutView->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // POINTS
    const int POINTS = obj["score"].toInt();

    if(POINTS == 1)
        newsRowView = new QLabel("1 point");
    else
        newsRowView = new QLabel(QString("%1 points").arg(POINTS));

    layoutView->addWidget(newsRowView);

    // SPACER
    layoutView->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Fixed, QSizePolicy::Minimum));

    // VIEW BUTTON
    QPushButton * button = new QPushButton("VIEW");
    button->setFixedWidth(100);
    layoutView->addWidget(button);

    connect(button, &QPushButton::clicked, this, &NewsRowCustomView::OnViewClicked);
}

// PRIVATE SLOTS

void NewsRowCustomView::OnViewClicked()
{
    QDesktopServices::openUrl(mURL);
}
