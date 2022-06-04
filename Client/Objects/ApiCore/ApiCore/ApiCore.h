#ifndef INCLUDED_APICORE_H
#define INCLUDED_APICORE_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

namespace Photon
{
    class ApiCore : public QObject
    {
        Q_OBJECT
    public:
        ApiCore(QObject* parent = nullptr);
        virtual ~ApiCore();

        void login(QString username, QString password);
        void logout();
        void listItems();        
    signals:
        void loginSuccessful();
        void loginFailed();
        void logoutSuccessful();
        void logoutFailed();
    private slots:
        void loginFinished();
        void logoutFinished();
        void listItemsFinished();
    private:
        QNetworkAccessManager* m_networkAccessManager;
    };
}

#endif // INCLUDED_APICORE_H
