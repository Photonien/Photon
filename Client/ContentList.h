#ifndef INCLUDED_CONTENTLIST_H
#define INCLUDED_CONTENTLIST_H

#include <QWidget>
#include <QTreeView>

namespace Photon
{
    class ContentList : public QWidget
    {
        Q_OBJECT

    public:
        ContentList(QWidget *parent);

        QTreeView* tree;
    };
}

#endif // INCLUDED_CONTENTLIST_H
