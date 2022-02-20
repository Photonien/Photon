#ifndef INCLUDED_APICORE_H
#define INCLUDED_APICORE_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>

namespace Photon
{
    class ApiCore : public QObject
    {
        Q_OBJECT
    public:
        ApiCore(QObject* parent = nullptr);
        virtual ~ApiCore();

        void post(const QJsonObject& json, QUrl relativeUrl, QNetworkReply* reply);
        void get(QUrl relativeUrl, QNetworkReply* reply);
        
    private:
        QNetworkAccessManager* m_networkAccessManager;
        QNetworkReply* m_reply;
        QNetworkRequest* m_request;
    };
}

#endif // INCLUDED_APICORE_H
