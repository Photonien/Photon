#include "ContentView.h"

#include <QVBoxLayout>
#include <QHeaderView>

using namespace Photon;

ContentView::ContentView(QWidget* parent)
    : QWidget(parent)
{   
    QLayout *lo = new QVBoxLayout(this);
    createActions();

    table = new QTableWidget(4, 4 , this);
    table->setHorizontalHeaderLabels(QStringList() << "Header1" << "Header2" << "Header3" << "Header4");
    table->verticalHeader()->hide();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->setItem(0, 0, new QTableWidgetItem("Item1"));
    table->setItem(0, 1, new QTableWidgetItem("Item2"));
    table->setItem(0, 2, new QTableWidgetItem("Item3"));
    table->setItem(0, 3, new QTableWidgetItem("Item4"));
    table->setContextMenuPolicy(Qt::CustomContextMenu);
    
    connect(table, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
    connect(table->horizontalHeader(), SIGNAL(sectionDoubleClicked(int logicalIndex)), this, SLOT(headerDoubleClicked(int logicalIndex)));
    
    setLayout(lo);
    lo->addWidget(table);
    lo->setSpacing(5);
}

void ContentView::createActions()
{
    contentViewMenu = new QMenu(this);

    insertRowUpAction = new QAction(tr("&Insert Row to Upside"), this);
    contentViewMenu->addAction(insertRowUpAction);
    
    insertRowDownAction = new QAction(tr("&Insert Row to Downside"), this);
    contentViewMenu->addAction(insertRowDownAction);

    insertColumnToLeftAction = new QAction(tr("&Insert Column to Leftside"), this);
    contentViewMenu->addAction(insertColumnToLeftAction);

    insertColumnToRightAction = new QAction(tr("&Insert Column to Rightside"), this);
    contentViewMenu->addAction(insertColumnToRightAction);
    
    deleteRowAction = new QAction(tr("&Delete Row"), this);
    contentViewMenu->addAction(deleteRowAction);
    
    deleteColumnAction = new QAction(tr("&Delete Column"), this);
    contentViewMenu->addAction(deleteColumnAction);
    
    moveUpAction = new QAction(tr("&Move Row Upside"), this);
    contentViewMenu->addAction(moveUpAction);

    moveDownAction = new QAction(tr("&Move Row Downside"), this);
    contentViewMenu->addAction(moveDownAction);
}

void ContentView::onCustomContextMenu(const QPoint &point)
{
    QModelIndex index = table->indexAt(point);
    if (index.isValid())
    {
        contentViewMenu->exec(table->viewport()->mapToGlobal(point));
    }
}

void ContentView::headerDoubleClicked(int logicaIndex)
{
    table->item(0,logicaIndex)->setText("berat");
}