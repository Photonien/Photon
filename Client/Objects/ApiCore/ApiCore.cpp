#include "ApiCore/ApiCore.h"
using namespace Photon;

ApiCore::ApiCore(QObject *parent) : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager(this);
}

ApiCore::~ApiCore()
{
}

void ApiCore::login(QString username, QString password)
{
    QJsonObject json;
    json["Username"] = username;
    json["Password"] = password;

    QNetworkRequest request;
    QUrl baseUrl("http://localhost:6000/auth/login");
    request.setUrl(baseUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = 
        m_networkAccessManager->post(request, QJsonDocument(json).toJson());

    connect(reply, SIGNAL(finished()), this, SLOT(loginFinished()));
}

void ApiCore::logout()
{
    QNetworkRequest request;
    QUrl baseUrl("http://localhost:6000//auth/logout");
    request.setUrl(baseUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = 
        m_networkAccessManager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(logoutFinished()));
}

void ApiCore::loginFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*> (QObject::sender());
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes);
        QJsonObject jsonObject = jsonDoc.object();
        if (jsonObject["Message"].toString() == "Log on with admin")
        {
            emit loginSuccessful();
        }
        else
        {
            emit loginFailed();
        }
    }
    else
    {
        emit loginFailed();
    }
}

void ApiCore::logoutFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*> (QObject::sender());
    if (reply->error() == QNetworkReply::NoError)
    {
        emit logoutSuccessful();
    }
    else
    {
        emit logoutFailed();
    }
}

void ApiCore::listItems()
{
    QNetworkRequest request;
    QUrl baseUrl("http://localhost:6000/items/");
    request.setUrl(baseUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = 
        m_networkAccessManager->get(request);
    
    connect(reply, SIGNAL(finished()), this, SLOT(listItemsFinished()));
}

void ApiCore::listItemsFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*> (QObject::sender());
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes);
        QJsonArray jsonArray = jsonDoc.array();
        for(int i = 0; i < jsonArray.size(); i++)
        {
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            std::string name = jsonObject[QString("Content")].toString().toStdString();
        }
        // TODO: Capture content
    }
}
