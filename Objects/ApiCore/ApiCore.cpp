#include "ApiCore/ApiCore.h"

using namespace Photon;

ApiCore::ApiCore(QString apiUrl, QObject *parent) : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager(this);
    m_apiUrl = apiUrl;
    successfulLogin = false;
}

ApiCore::~ApiCore()
{
}

QNetworkReply* ApiCore::post(const QJsonObject &json, QString relativeUrl)
{
    QNetworkRequest request;
    QUrl baseUrl(m_apiUrl + relativeUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    return m_networkAccessManager->post(request, QJsonDocument(json).toJson());
}

void ApiCore::get(QString relativeUrl, QNetworkReply *reply)
{
    QNetworkRequest request;
    QUrl baseUrl(m_apiUrl + relativeUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    reply = m_networkAccessManager->get(request);
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

bool ApiCore::isLoggedIn()
{
    return successfulLogin;
}

void ApiCore::logout()
{
    QNetworkReply *reply = nullptr;
    get("/logout", reply);
    // Check reply
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes);
        QJsonObject jsonObject = jsonDoc.object();
        if (jsonObject["status"].toString() == "success")
        {
            // Logout successful
        }
    }
}
/*
void ApiCore::addNewUser(QString user, QString password)
{
    QJsonObject json;
    json["user"] = user;
    json["password"] = password;
    QNetworkReply *reply = nullptr;
    post(json, QUrl("register"), reply);
    // Check reply
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes);
        QJsonObject jsonObject = jsonDoc.object();
        if (jsonObject["status"].toString() == "success")
        {
            // Add user successful
        }
    }
}

void ApiCore::listAllUsers()
{
    QNetworkReply *reply = nullptr;
    get(QUrl("/listUsers"), reply);
    // Check reply
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes);
        QJsonObject jsonObject = jsonDoc.object();
        if (jsonObject["status"].toString() == "success")
        {
            // List users successful
        }
    }
}

void ApiCore::deleteAllUsers()
{
    QNetworkReply *reply = nullptr;
    get(QUrl("/users/delete/all"), reply);
    // Check reply
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes);
        QJsonObject jsonObject = jsonDoc.object();
        if (jsonObject["status"].toString() == "success")
        {
            // Delete users successful
        }
    }
}

void ApiCore::listItems()
{
    QNetworkReply *reply = nullptr;
    get(QUrl("/items/"), reply);
    // Check reply
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes);
        QJsonObject jsonObject = jsonDoc.object();
        if (jsonObject["status"].toString() == "success")
        {
            // List items successful
        }
    }
}*/