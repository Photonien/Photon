#include "ContentList.h"

#include <QVBoxLayout>
#include <QListWidget>

using namespace Photon;

ContentList::ContentList(QWidget* parent)
    : QWidget(parent)
{    
    QLayout *lo = new QVBoxLayout(this);
    QListWidget* mList = new QListWidget(this);

    mList->addItem("Testing1");
    mList->addItem("Testing2");
    mList->addItem("Testing3");
    setLayout(lo);
    lo->addWidget(mList);
    lo->setSpacing(5);
}