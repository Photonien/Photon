#include "ApiCore.h"

using namespace Photon;

constexpr auto API_URL = "http://localhost:6000/";

ApiCore::ApiCore(QObject* parent) : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager(this);
    m_request = new QNetworkRequest(QUrl(API_URL));
    m_reply = nullptr;
}

ApiCore::~ApiCore()
{

}

void ApiCore::post(const QJsonObject& json, QNetworkReply* reply, QUrl relativeUrl)
{
    QNetworkRequest request;
    QUrl baseUrl(API_URL);
    request.setUrl(baseUrl.resolved(relativeUrl));

    reply = m_networkAccessManager->post(request, QJsonDocument(json).toJson());
}

void ApiCore::get(const QNetworkRequest* request, QNetworkReply* reply)
{
    reply = m_networkAccessManager->get(*request);
}
