#include "LoginDialog.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QObject>
#include <QStyle>
#include <QSettings>
#include <QCheckBox>
#include <QMessageBox>

using namespace Photon;

LoginDialog::LoginDialog(QDialog *parent)
    : QDialog(parent)
{
    saveSettings = false;

    QGridLayout *layout = new QGridLayout;
    dialog = new QDialog(this);
    dialog->setWindowTitle("Connect to Server");
    dialog->setLayout(layout);
    dialog->setFixedSize(300, 100);

    QLabel *serverIPlabel = new QLabel("Server IP:", dialog);
    layout->addWidget(serverIPlabel, 0, 0);
    serverIPlabel->setText("Server IP:");
    serverIPEdit = new QLineEdit(dialog);
    layout->addWidget(serverIPEdit, 0, 1);
    
    QLabel *userNamelabel = new QLabel("Server IP:", dialog);
    layout->addWidget(userNamelabel, 1, 0);
    userNamelabel->setText("User Name:");
    userNameEdit = new QLineEdit(dialog);
    layout->addWidget(userNameEdit, 1, 1);

    QLabel *passwordlabel = new QLabel("Server IP:", dialog);
    layout->addWidget(passwordlabel, 2, 0);
    passwordlabel->setText("User Name:");
    passwordEdit = new QLineEdit(dialog);
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordEdit, 2, 1);

    QCheckBox* saveAuthBox = new QCheckBox("Save authentication", dialog);
    layout->addWidget(saveAuthBox, 3, 0, 1, 2);
    connect(saveAuthBox, SIGNAL(stateChanged(int)), this, SLOT(saveAuth(int)));
    
    QPushButton *connectButton = new QPushButton(dialog);
    connectButton->setText("Connect");
    connectButton->setIcon(this->style()->standardIcon(QStyle::SP_CommandLink));
    layout->addWidget(connectButton, 4, 0);
    connect(connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));

    QPushButton *cancelButton = new QPushButton(dialog);
    cancelButton->setText("Cancel");
    cancelButton->setIcon(this->style()->standardIcon(QStyle::SP_DialogCancelButton));
    layout->addWidget(cancelButton, 4, 1);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

    this->setLayout(layout);

    checkSettings();
}

void LoginDialog::checkSettings()
{
    QSettings settings("Photon", "Photon");
    serverIPEdit->setText(settings.value("serverIP", "").toString());
    userNameEdit->setText(settings.value("userName", "").toString());
    passwordEdit->setText(settings.value("password", "").toString());
}

void LoginDialog::connectToServer()
{
    QString serverAddr = serverIPEdit->text();
    QString user = userNameEdit->text();
    QString pass = passwordEdit->text();
    if (saveSettings)
    {
        QSettings settings("Photon", "Photon");
        settings.setValue("serverIP", serverAddr);
        settings.setValue("userName", user);
        settings.setValue("password", pass);
    }

    ApiCore* api = new ApiCore(serverAddr);
    api->login(user, pass);
    connect(api, SIGNAL(loginSuccessful()), this, SLOT(loginSuccess()));
    connect(api, SIGNAL(loginFailed()), this, SLOT(loginFailed()));
}

void LoginDialog::loginSuccess()
{
    this->close();
    emit success();
}

void LoginDialog::loginFailed()
{
    QMessageBox::warning(this, "Login Failed",
        "Login failed. Please check your username and password.");
    emit fail();
}

void LoginDialog::cancel()
{
    this->reject();
}

void LoginDialog::saveAuth(int state)
{
    if (state == Qt::Checked)
    {
        saveSettings = true;        
    }
}
