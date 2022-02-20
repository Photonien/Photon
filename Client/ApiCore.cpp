#include "ApiCore.h"

using namespace Photon;

constexpr auto API_URL = "http://localhost:6000/";

ApiCore::ApiCore(QObject* parent) : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager(this);
}

ApiCore::~ApiCore()
{

}

void ApiCore::post(const QJsonObject& json, QUrl relativeUrl, QNetworkReply* reply)
{
    QNetworkRequest request;
    QUrl baseUrl(API_URL);
    request.setUrl(baseUrl.resolved(relativeUrl));

    reply = m_networkAccessManager->post(request, QJsonDocument(json).toJson());
}

void ApiCore::get(QUrl relativeUrl, QNetworkReply* reply)
{
    QNetworkRequest request;
    QUrl baseUrl(API_URL);
    request.setUrl(baseUrl.resolved(relativeUrl));

    reply = m_networkAccessManager->get(request);
}
