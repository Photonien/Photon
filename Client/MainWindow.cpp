#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>

#include "ContentList.h"

using namespace Photon;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_ui = new Ui::MainWindow();
    createActions();
    setupMenuBar();
    ContentList* contentList = new ContentList(this);
    this->setCentralWidget(contentList);
    m_ui->setupUi(this);

    connect(m_ui->pushButton, SIGNAL(clicked()), this, SLOT(onPushButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
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
    m_ui->plainTextEdit->appendPlainText(QString("Downloading %1 of %2 bytes").arg(bytesReceived).arg(bytesTotal));
}

//And finally, my onResult slot
void MainWindow::onResult() 
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*> (QObject::sender());

    if (reply->error() != QNetworkReply::NoError)
    {
        m_ui->plainTextEdit->appendPlainText("Error :" + reply->errorString());
        return;
    }

    reply->deleteLater();

    m_ui->plainTextEdit->appendPlainText("Response: " + reply->readAll());
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

    menuBar()->addSeparator();

    QMenu *aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createActions()
{
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setShortcut(tr("Ctrl+A"));
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save the document to disk"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    printAction = new QAction(tr("&Print"), this);
    printAction->setShortcut(tr("Ctrl+P"));
    printAction->setStatusTip(tr("Print the document"));
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

    exportAction = new QAction(tr("&Export"), this);
    exportAction->setShortcut(tr("Ctrl+E"));
    exportAction->setStatusTip(tr("Export the document"));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportDoc()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(closeApp()));

    connectAction = new QAction(tr("&Connect"), this);
    connectAction->setShortcut(tr("Ctrl+C"));
    connectAction->setStatusTip(tr("Connect to the server"));
    connect(connectAction, SIGNAL(triggered()), this, SLOT(onPushButtonClicked()));

    disconnectAction = new QAction(tr("&Disconnect"), this);
    disconnectAction->setShortcut(tr("Ctrl+D"));
    disconnectAction->setStatusTip(tr("Disconnect from the server"));
    connect(disconnectAction, SIGNAL(triggered()), this, SLOT(onPushButtonClicked()));
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

