#include "contentview.h"
#include "ui_contentview.h"
#include "networkmanager.h"

// Networking Handler
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

// JSON Parsing
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue> // handle the data recieved

// Interface
#include <QByteArray>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

#include <string>
using namespace std;


ContentView::ContentView(QWidget *parent)
    : QMainWindow(parent)
    , mPanelStories(nullptr)
    , mNetMan(new QNetworkAccessManager(this))
    , mNetReply(nullptr)
    , mDataBuffer(new QByteArray)
{
//    ui->setupUi(this);
    // == WINDOW SETTINGS ==
    setWindowTitle("Simple Hacker News Reader");

    const int WIN_W = 1024;
    const int WIN_H = 550;
    setFixedSize(WIN_W, WIN_H);

    // create GUI
    BuildWindow();
}

ContentView::~ContentView()
{
    delete ui;
}

void ContentView::BuildWindow()
{
    // -- MAIN WIDGET --
    QWidget * content = new QWidget;
    setCentralWidget(content);

    QVBoxLayout * layoutMain = new QVBoxLayout;
    content->setLayout(layoutMain);

    // -- REFRESH BUTTON --
    mButtonRefresh = new QPushButton("REFRESH");
    mButtonRefresh->setFixedWidth(200);

    layoutMain->addWidget(mButtonRefresh, 0, Qt::AlignHCenter);

    connect(mButtonRefresh, &QPushButton::clicked, this, &ContentView::OnRefreshClicked);

    // -- VERT SPACER --
    layoutMain->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void ContentView::ReadStory()
{
    const QString STR = QString("https://hacker-news.firebaseio.com/v0/item/%1.json").arg(mLatestStoriesID[mCurrStory++]);
    const QUrl STORY_URL(STR);

    mNetReply = mNetMan->get(QNetworkRequest(STORY_URL));

    connect(mNetReply, &QIODevice::readyRead, this, &ContentView::OnDataReadyToRead);
    connect(mNetReply, &QNetworkReply::finished, this, &ContentView::OnStoryReadFinished);
}

void ContentView::NetworkCleanup()
{
    mNetReply->deleteLater();
    mNetReply = nullptr;

    mDataBuffer->clear();
}

// == PRIVATE SLOTS ==
void ContentView::OnRefreshClicked()
{
    // disable button while processing data
    mButtonRefresh->setEnabled(false);

    // -- DOWNLOAD LIST OF STORIES --
    const QUrl STORIES_LIST_URL("https://hacker-news.firebaseio.com/v0/newstories.json");
    mNetReply = mNetMan->get(QNetworkRequest(STORIES_LIST_URL));

    connect(mNetReply, &QIODevice::readyRead, this, &ContentView::OnDataReadyToRead);
    connect(mNetReply, &QNetworkReply::finished, this, &ContentView::OnListReadFinished);
}

void ContentView::OnDataReadyToRead()
{
    mDataBuffer->append(mNetReply->readAll());
}

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

void ContentView::OnStoryReadFinished()
{
    QJsonDocument doc = QJsonDocument::fromJson(*mDataBuffer);

    // -- ADD STORY --
    NetworkManager * entry = new NetworkManager(mCurrStory, doc.object());
    mPanelStories->layout()->addWidget(entry);

    // -- CLEAN UP --
    NetworkCleanup();

    // -- NEXT STORY OR FINISH --
    if(mCurrStory < NUM_STORIES_SHOWED)
        ReadStory();
    else
        mButtonRefresh->setEnabled(true);
}


