#include "ApiCore/ApiCore.h"

using namespace Photon;

constexpr auto API_URL = "http://localhost:6000/";

ApiCore::ApiCore(QObject *parent) : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager(this);
}

ApiCore::~ApiCore()
{
}

void ApiCore::post(const QJsonObject &json, QUrl relativeUrl, QNetworkReply *reply)
{
    QNetworkRequest request;
    QUrl baseUrl(API_URL);
    request.setUrl(baseUrl.resolved(relativeUrl));

    reply = m_networkAccessManager->post(request, QJsonDocument(json).toJson());
}

void ApiCore::get(QUrl relativeUrl, QNetworkReply *reply)
{
    QNetworkRequest request;
    QUrl baseUrl(API_URL);
    request.setUrl(baseUrl.resolved(relativeUrl));

    reply = m_networkAccessManager->get(request);
}

void ApiCore::login(QString username, QString password)
{
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;
    QNetworkReply *reply = nullptr;
    post(json, QUrl("login"), reply);
    // Check reply
    try
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray bytes = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes);
            QJsonObject jsonObject = jsonDoc.object();
            if (jsonObject["status"].toString() == "success")
            {
                // Login successful
            }
        }
    }
    catch (const std::exception &e)
    {
        qDebug() << e.what();
    }
}

void ApiCore::logout()
{
    QNetworkReply *reply = nullptr;
    get(QUrl("logout"), reply);
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
}