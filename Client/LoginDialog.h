#ifndef INCLUDED_LOGINDIALOG_H
#define INCLUDED_LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>

#include "ApiCore/ApiCore.h"

namespace Photon
{
    class LoginDialog : public QDialog
    {
        Q_OBJECT

    public:
        LoginDialog(QDialog *parent = 0);
    private slots:
        void connectToServer();
        void cancel();
        void saveAuth(int state);
        void loginSuccess();
        void loginFailed();
    signals:
        void success();
        void fail();
    private:
        void checkSettings();
        bool saveSettings;

        QDialog* dialog;
        QLineEdit *serverIPEdit;
        QLineEdit *userNameEdit;
        QLineEdit *passwordEdit;
    };
}

#endif // INCLUDED_LOGINDIALOG_H
