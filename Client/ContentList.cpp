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

    contextMenu = new QMenu(this);
    createMenuActions();

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
    tree->setContextMenuPolicy(Qt::CustomContextMenu);
    
    connect(tree, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));

    setLayout(lo);
    lo->addWidget(tree);
    lo->setSpacing(5);
}

void ContentList::createMenuActions()
{
    openAction = new QAction(tr("&Open"), this);
    openAction->setStatusTip(tr("Open this model"));
    openAction->setIcon(this->style()->standardIcon(QStyle::SP_DirOpenIcon));
    //connect(openAction, SIGNAL(triggered()), this, SLOT(//FillHere));
    contextMenu->addAction(openAction);
    
    addAction = new QAction(tr("&Add"), this);
    addAction->setStatusTip(tr("Add a new model"));
    addAction->setIcon(this->style()->standardIcon(QStyle::SP_FileDialogNewFolder));
    //connect(addAction, SIGNAL(triggered()), this, SLOT(//FillHere));
    contextMenu->addAction(addAction);

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setStatusTip(tr("Delete this model"));
    deleteAction->setIcon(this->style()->standardIcon(QStyle::SP_TrashIcon));
    //connect(deleteAction, SIGNAL(triggered()), this, SLOT(//FillHere));
    contextMenu->addAction(deleteAction);
}

void ContentList::onCustomContextMenu(const QPoint &point)
{
    QModelIndex index = tree->indexAt(point);
    if (index.isValid() && index.parent().isValid())
    {
        contextMenu->exec(tree->viewport()->mapToGlobal(point));
    }    
}