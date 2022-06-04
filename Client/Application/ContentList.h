#ifndef INCLUDED_CONTENTLIST_H
#define INCLUDED_CONTENTLIST_H

#include <QWidget>
#include <QTreeView>
#include <QMenu>
#include <QAction>

namespace Photon
{
    class ContentList : public QWidget
    {
        Q_OBJECT

    public:
        ContentList(QWidget *parent);

        QTreeView* tree;
    private slots:
        void onCustomContextMenu(const QPoint &point);

    private:
        void createMenuActions();
        QMenu* contextMenu;
        QAction* openAction;
        QAction* addAction;
        QAction* deleteAction;
    };
}

#endif // INCLUDED_CONTENTLIST_H
