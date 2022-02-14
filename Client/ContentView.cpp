#include "ContentView.h"

#include <QVBoxLayout>

using namespace Photon;

ContentView::ContentView(QWidget* parent)
    : QWidget(parent)
{   
    QLayout *lo = new QVBoxLayout(this);
    table = new QTableWidget(4, 4 , this);
    table->setVerticalHeaderLabels(QStringList() << "1" << "2" << "3" << "4");
    table->setHorizontalHeaderLabels(QStringList() << "Header1" << "Header2" << "Header3" << "Header4");
    table->setItem(0, 0, new QTableWidgetItem("Item1"));
    table->setItem(0, 1, new QTableWidgetItem("Item2"));
    table->setItem(0, 2, new QTableWidgetItem("Item3"));
    table->setItem(0, 3, new QTableWidgetItem("Item4"));

    setLayout(lo);
    lo->addWidget(table);
    lo->setSpacing(5);
}