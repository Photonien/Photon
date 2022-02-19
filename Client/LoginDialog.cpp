#include "LoginDialog.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStyle>

using namespace Photon;

LoginDialog::LoginDialog(QDialog *parent)
    : QDialog(parent)
{
    QGridLayout *layout = new QGridLayout;
    dialog = new QDialog(this);
    dialog->setWindowTitle("Connect to Server");
    dialog->setLayout(layout);
    dialog->setFixedSize(300, 100);

    QLabel *serverIPlabel = new QLabel("Server IP:", dialog);
    layout->addWidget(serverIPlabel, 0, 0);
    serverIPlabel->setText("Server IP:");
    QLineEdit *serverIPEdit = new QLineEdit(dialog);
    layout->addWidget(serverIPEdit, 0, 1);
    
    QLabel *userNamelabel = new QLabel("Server IP:", dialog);
    layout->addWidget(userNamelabel, 1, 0);
    userNamelabel->setText("User Name:");
    QLineEdit *userNameEdit = new QLineEdit(dialog);
    layout->addWidget(userNameEdit, 1, 1);

    QLabel *passwordlabel = new QLabel("Server IP:", dialog);
    layout->addWidget(passwordlabel, 2, 0);
    passwordlabel->setText("User Name:");
    QLineEdit *passwordEdit = new QLineEdit(dialog);
    layout->addWidget(passwordEdit, 2, 1);

    QPushButton *connectButton = new QPushButton(dialog);
    connectButton->setText("Connect");
    connectButton->setIcon(this->style()->standardIcon(QStyle::SP_CommandLink));
    layout->addWidget(connectButton, 3, 0);
    // Connect the button to the slot

    QPushButton *cancelButton = new QPushButton(dialog);
    cancelButton->setText("Cancel");
    cancelButton->setIcon(this->style()->standardIcon(QStyle::SP_DialogCancelButton));
    layout->addWidget(cancelButton, 3, 1);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(QDialog::done(0)));
    this->setLayout(layout);
}