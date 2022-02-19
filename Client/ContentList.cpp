#include "ContentList.h"

#include <QVBoxLayout>
#include <QStandardItem>
#include <QStandardItemModel>

using namespace Photon;

ContentList::ContentList(QWidget* parent)
    : QWidget(parent)
{    
    QLayout *lo = new QVBoxLayout(this);
    tree = new QTreeView(this);

    // Experimental temporary code
    QStandardItemModel* model = new QStandardItemModel(this);
    // Create the root item.
    QStandardItem* rootItem = new QStandardItem("Root");
    rootItem->setEditable(false);
    rootItem->setIcon(this->style()->standardIcon(QStyle::SP_DriveNetIcon));
    // Add the root item to the model.
    model->appendRow(rootItem);
    // Create the child items.
    QStandardItem* childItem1 = new QStandardItem("Child 1");
    QStandardItem* childItem2 = new QStandardItem("Child 2");
    // Add the child items to the root item.
    rootItem->appendRow(childItem1);
    rootItem->appendRow(childItem2);
    // for loop for each child item of rootItem
    for (int i = 0; i < rootItem->rowCount(); ++i)
    {
        rootItem->child(i)->setEditable(false);
        rootItem->child(i)->setIcon(this->style()->standardIcon(QStyle::SP_FileIcon));  
    }
    // Set the model to the tree view.
    tree->setModel(model);
    tree->setHeaderHidden(true);
    tree->setAnimated(true);
    tree->setSelectionMode(QAbstractItemView::SingleSelection);
    tree->setSelectionBehavior(QAbstractItemView::SelectRows);


    setLayout(lo);
    lo->addWidget(tree);
    lo->setSpacing(5);
}