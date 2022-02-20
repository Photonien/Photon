#ifndef INCLUDED_APICORE_H
#define INCLUDED_APICORE_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QString>

namespace Photon
{
    class ApiCore : public QObject
    {
        Q_OBJECT
    public:
        ApiCore(QString apiUrl, QObject* parent = nullptr);
        virtual ~ApiCore();

        void login(QString username, QString password);
        bool isLoggedIn();

        void logout();
        //void addNewUser(QString user, QString password);
        //void listAllUsers();
        //void deleteAllUsers();
        //void listItems();
    signals:
        void loginSuccessful();
        void loginFailed();
    private slots:
        void loginFinished();
    private:
        QNetworkReply* post(const QJsonObject& json, QString relativeUrl);
        void get(QString relativeUrl, QNetworkReply* reply);
        
        QNetworkAccessManager* m_networkAccessManager;
        QString m_apiUrl;

        bool successfulLogin;
    };
}

#endif // INCLUDED_APICORE_H
