#ifndef INCLUDED_CONTENTVIEW_H
#define INCLUDED_CONTENTVIEW_H

#include <QWidget>
#include <QTableWidget>

namespace Photon
{
    class ContentView : public QWidget
    {
        Q_OBJECT

    public:
        ContentView(QWidget *parent);
    private:
        QTableWidget* table;
    };
}

#endif // INCLUDED_CONTENTVIEW_H
