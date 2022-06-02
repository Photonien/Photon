#ifndef INCLUDED_APICORE_H
#define INCLUDED_APICORE_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

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
        void login(QString username, QString password);
        void logout();
        void addNewUser(QString user, QString password);
        void listAllUsers();
        void deleteAllUsers();
        void listItems();
    private:
        QNetworkAccessManager* m_networkAccessManager;
    };
}

#endif // INCLUDED_APICORE_H
