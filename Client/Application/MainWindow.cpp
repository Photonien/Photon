#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>

#include "ContentList.h"
#include "ContentView.h"

using namespace Photon;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_ui = new Ui::MainWindow();
    m_ui->setupUi(this);
    
    api = new ApiCore();
    login = new LoginDialog();
    login->setApi(api);

    connect(login, SIGNAL(success()), this, SLOT(getContent()));
    connect(login, SIGNAL(fail()), this, SLOT(freezeContent()));

    createActions();
    setupMenuBar();
    createWidgets();    
    
    statusBar()->showMessage("Ready");
    
    this->setCentralWidget(splitter);
    freezeContent();
    emit connectAction->trigger();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::createWidgets()
{
    ContentList* contentList = new ContentList(this);
    ContentView* contentView = new ContentView(this);

    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    tabWidget->addTab(contentView, "Content View");

    splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setHandleWidth(1);
    splitter->addWidget(contentList);
    splitter->addWidget(tabWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 4);
}

void MainWindow::onPushButtonClicked()
{
    QString myUrl = "http://localhost:6000/listtodo";

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QUrl url(myUrl);
    request.setUrl(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloading(qint64,qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(onResult()));
}

void MainWindow::downloading(qint64 bytesReceived, qint64 bytesTotal) 
{
    m_ui->statusBar->showMessage(QString("Downloading %1 of %2").arg(bytesReceived).arg(bytesTotal));
}

//And finally, my onResult slot
void MainWindow::onResult() 
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*> (QObject::sender());

    if (reply->error() != QNetworkReply::NoError)
    {
        m_ui->statusBar->showMessage("Error :" + reply->errorString());
        return;
    }

    reply->deleteLater();
    m_ui->statusBar->showMessage("Response :" + reply->readAll());
}

void MainWindow::setupMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(saveAction);
    fileMenu->addAction(printAction);
    fileMenu->addAction(exportAction);
    fileMenu->addAction(exitAction);

    QMenu *connectionMenu = menuBar()->addMenu(tr("&Connection"));
    connectionMenu->addAction(connectAction);
    connectionMenu->addAction(disconnectAction);

    QMenu *aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createActions()
{
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setShortcut(tr("Ctrl+A"));
    aboutAction->setStatusTip(tr("Show the application's About box"));
    aboutAction->setIcon(this->style()->standardIcon(QStyle::SP_MessageBoxInformation));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save the document to disk"));
    saveAction->setIcon(this->style()->standardIcon(QStyle::SP_DriveFDIcon));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    printAction = new QAction(tr("&Print"), this);
    printAction->setShortcut(tr("Ctrl+P"));
    printAction->setStatusTip(tr("Print the document"));
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

    exportAction = new QAction(tr("&Export"), this);
    exportAction->setShortcut(tr("Ctrl+E"));
    exportAction->setStatusTip(tr("Export the document"));
    exportAction->setIcon(this->style()->standardIcon(QStyle::SP_ArrowRight));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportDoc()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    exitAction->setIcon(this->style()->standardIcon(QStyle::SP_DockWidgetCloseButton));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(closeApp()));

    connectAction = new QAction(tr("&Connect"), this);
    connectAction->setShortcut(tr("Ctrl+C"));
    connectAction->setStatusTip(tr("Connect to the server"));
    connectAction->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
    connect(connectAction, SIGNAL(triggered()), this, SLOT(connectToServer()));

    disconnectAction = new QAction(tr("&Disconnect"), this);
    disconnectAction->setShortcut(tr("Ctrl+D"));
    disconnectAction->setStatusTip(tr("Disconnect from the server"));
    disconnectAction->setIcon(this->style()->standardIcon(QStyle::SP_BrowserStop));
    connect(disconnectAction, SIGNAL(triggered()), this, SLOT(disconnectServer()));

    disconnectAction->setEnabled(false);
    connectAction->setEnabled(true);

    m_ui->toolBar->addAction(connectAction);
    m_ui->toolBar->addAction(disconnectAction);
    m_ui->toolBar->addAction(exitAction);
}

const char *htmlText =
"<HTML>"
"<p><b>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod"
"tempor incididunt ut labore et dolore <c>magna aliqua</c>. Ut enim ad minim veniam,"
"quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo"
"consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse"
"cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non"
"proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</b></p>"
"<ul>"
"<li>Lorem ipsum dolor sit amet</li>"
"<li> consectetur adipisicing elit, sed do eiusmod</li>"
"<li>tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,</li>"
"<li>Lorem ipsum dolor.</li>"
"</HTML>";

void MainWindow::showAbout()
{
    QMessageBox::about(this, "About Photon", htmlText);
}

void MainWindow::closeApp()
{
    QMessageBox::StandardButton res = QMessageBox::question(this, "Photon",
                                                             "Are you sure to quit?",
                                                             QMessageBox::Yes | QMessageBox::No);
    if (res == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

void MainWindow::save()
{
    QMessageBox::information(this, "Photon", "The document has been saved!");
}

void MainWindow::print()
{
    QMessageBox::information(this, "Photon", "The document has been printed!");
}

void MainWindow::exportDoc()
{
    QMessageBox::information(this, "Photon", "The document has been exported!");
}

void MainWindow::connectToServer()
{  
    disconnectAction->setEnabled(true);
    connectAction->setEnabled(false);
    login->show();
}

void MainWindow::getContent()
{
    m_ui->statusBar->showMessage("Connected to server");
    api->listItems();
    disconnectAction->setEnabled(true);
    connectAction->setEnabled(false);

    for(auto child:splitter->findChildren<QWidget *>())
    {
        child->setEnabled(true);
    }
    splitter->setEnabled(true);
    
}

void MainWindow::freezeContent()
{
    m_ui->statusBar->showMessage("Disconnected from server");
    for(auto child:splitter->findChildren<QWidget *>())
    {
        child->setEnabled(false);
    }
    splitter->setEnabled(false);

    disconnectAction->setEnabled(false);
    connectAction->setEnabled(true);
}

void MainWindow::disconnectServer()
{
    disconnectAction->setEnabled(false);
    connectAction->setEnabled(true);
    api->logout();
    connect(api, SIGNAL(logoutSuccessful()), this, SLOT(freezeContent()));
    QMessageBox::information(this, "Photon", "The server has been disconnected!");
}

void MainWindow::tabClose(int index)
{
    tabWidget->widget(index)->close();
}