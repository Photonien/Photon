#ifndef INCLUDED_LOGINDIALOG_H
#define INCLUDED_LOGINDIALOG_H

#include <QDialog>

namespace Photon
{
    class LoginDialog : public QDialog
    {
        Q_OBJECT

    public:
        LoginDialog(QDialog *parent = 0);
    private:
        QDialog* dialog;
    };
}

#endif // INCLUDED_LOGINDIALOG_H
