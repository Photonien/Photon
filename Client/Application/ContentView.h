#ifndef INCLUDED_CONTENTVIEW_H
#define INCLUDED_CONTENTVIEW_H

#include <QWidget>
#include <QTableWidget>
#include <QMenu>
#include <QAction>

namespace Photon
{
    class ContentView : public QWidget
    {
        Q_OBJECT

    public:
        ContentView(QWidget *parent);
    private:
        void createActions();
        QTableWidget* table;
        QMenu* contentViewMenu;
        QAction* insertRowUpAction;
        QAction* insertRowDownAction;
        QAction* insertColumnToLeftAction;
        QAction* insertColumnToRightAction;
        QAction* deleteRowAction;
        QAction* deleteColumnAction;
        QAction* moveUpAction;
        QAction* moveDownAction;
    private slots:
        void onCustomContextMenu(const QPoint &point);
        void headerDoubleClicked(int logicaIndex);
    };
}

#endif // INCLUDED_CONTENTVIEW_H
