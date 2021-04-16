#include "contentview.h"
#include "ui_contentview.h"
#include "newsrowcustomview.h"

// Networking Handler
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

// JSON Parsing
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue> // handle the data receive

// UI
#include <QByteArray>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout> // VStack
#include <QPalette>

#include <string>
using namespace std;

ContentView::ContentView(QWidget *parent): QMainWindow(parent)
    , mPanelStories(nullptr)
    , mNetMan(new QNetworkAccessManager(this))
    , mNetReply(nullptr)
    , mDataBuffer(new QByteArray)
{

    // WINDOW'S TOP HEADER
    setWindowTitle("HustleFlow: Hacker News Reader");

    // WINDOW'S DIMENSIONS
    const int WIN_W = 1180;
    const int WIN_H = 620;
    setFixedSize(WIN_W, WIN_H);

    // create GUI
    BuildWindow();
}

// DESTRUCTOR
ContentView::~ContentView()
{
    delete ui;
}

// ======================================== CONTENT VIEW EXTENSIONS ========================================

// UI
void ContentView::BuildWindow()
{

    // BLANK WINDOW READY TO STORE WIDGETS
    QWidget *content = new QWidget;
    setCentralWidget(content);

    // APPLY VSTACK
    QVBoxLayout *vstack = new QVBoxLayout;
    content->setLayout(vstack);

    // FONT EXTENSION
    QFont titleFont;
    titleFont.setPointSize(22);
    titleFont.setBold(true);

    // NAV BAR TITLE
    QLabel *topBarTitle = new QLabel(QString("READ WHAT'S HAPPENING NOW"));
    topBarTitle->setFont(titleFont);

    // REFRESH BUTTON
    refreshButton = new QPushButton("REFRESH");
    refreshButton->setFixedWidth(200);

    vstack->addWidget(topBarTitle, 0, Qt::AlignHCenter);
    vstack->addWidget(refreshButton, 0, Qt::AlignHCenter);

    connect(refreshButton, &QPushButton::clicked, this, &ContentView::OnRefreshClicked);

    // VERT SPACER
    vstack->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

// DATA FETCHING
void ContentView::ReadStory()
{
    const QString STR = QString("https://hacker-news.firebaseio.com/v0/item/%1.json").arg(mLatestStoriesID[mCurrStory++]);
    const QUrl STORY_URL(STR);

    mNetReply = mNetMan->get(QNetworkRequest(STORY_URL));

    connect(mNetReply, &QIODevice::readyRead, this, &ContentView::OnDataReadyToRead);
    connect(mNetReply, &QNetworkReply::finished, this, &ContentView::OnStoryReadFinished);
}

// DESTRUCTIVE FUNCTION
void ContentView::NetworkCleanup()
{
    mNetReply->deleteLater();
    mNetReply = nullptr;

    mDataBuffer->clear();
}


// PRIVATE SLOT
void ContentView::OnRefreshClicked()
{
    // disable button while processing data
    refreshButton->setEnabled(false);
    refreshButton->setText("FETCHING...");

    // DOWNLOAD LIST OF STORIES
    const QUrl STORIES_LIST_URL("https://hacker-news.firebaseio.com/v0/newstories.json");
    mNetReply = mNetMan->get(QNetworkRequest(STORIES_LIST_URL));

    connect(mNetReply, &QIODevice::readyRead, this, &ContentView::OnDataReadyToRead);
    connect(mNetReply, &QNetworkReply::finished, this, &ContentView::OnListReadFinished);
}

// FETCHING DATA
void ContentView::OnDataReadyToRead()
{
    mDataBuffer->append(mNetReply->readAll());
}

// APPENDING CUSTOM ROW LIST
void ContentView::OnListReadFinished()
{
    QJsonDocument doc = QJsonDocument::fromJson(*mDataBuffer);
    QJsonArray array = doc.array();

    // -- STORE LATEST 10 STORIES ID --
    for(int i = 0; i < NUM_STORIES_SHOWED; ++i)
        mLatestStoriesID[i] = array[i].toInt();

    // -- CLEAN UP --
    NetworkCleanup();

    // -- SET UP PANEL STORIES --
    delete mPanelStories;

    mPanelStories = new QWidget;
    centralWidget()->layout()->addWidget(mPanelStories);

    QVBoxLayout * layout = new QVBoxLayout;
    mPanelStories->setLayout(layout);

    // -- START READING STORIES --
    mCurrStory = 0;

    ReadStory();
}


// WRAPPED UP SHOWING THE CONTENTS THAT LINK TO HACKER-NEWS
void ContentView::OnStoryReadFinished()
{
    refreshButton->setText("REFRESH");

    QJsonDocument doc = QJsonDocument::fromJson(*mDataBuffer);

    // ADD STORY
    NewsRowCustomView * entry = new NewsRowCustomView(mCurrStory, doc.object());
    mPanelStories->layout()->addWidget(entry);

    // CLEAN UP
    NetworkCleanup();

    // NEXT STORY OR FINISH
    if(mCurrStory < NUM_STORIES_SHOWED)
        ReadStory();
    else
        refreshButton->setEnabled(true);
}


