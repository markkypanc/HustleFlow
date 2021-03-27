#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ContentView; }
QT_END_NAMESPACE


class QByteArray;
class QNetworkAccessManager;
class QNetworkReply;
class QPushButton;


// MARK: - MAIN CONTENT VIEW
class ContentView : public QMainWindow
{
    Q_OBJECT

public:
    ContentView(QWidget *parent = nullptr);
    ~ContentView();

private:

    Ui::ContentView *ui;
    void BuildWindow();

    void ReadStory();

    void NetworkCleanup();

private slots:
    void OnRefreshClicked();

    void OnDataReadyToRead();
    void OnListReadFinished();
    void OnStoryReadFinished();

private:
    static const int NUM_STORIES_SHOWED = 10;

private:
    int mLatestStoriesID[NUM_STORIES_SHOWED];

    QPushButton * mButtonRefresh;

    QWidget * mPanelStories;

    QNetworkAccessManager * mNetMan;
    QNetworkReply * mNetReply;
    QByteArray * mDataBuffer;

    int mCurrStory;

};
#endif // CONTENTVIEW_H
