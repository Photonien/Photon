#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

using namespace Photon;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_ui = new Ui::MainWindow();
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