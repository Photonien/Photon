#include <QMainWindow>
#include <QTabWidget>
#include <QSplitter>

#include "LoginDialog.h"
#include "ApiCore/ApiCore.h"

namespace Ui
{
    class MainWindow;
}

namespace Photon
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void onPushButtonClicked();
        void downloading(qint64, qint64);
        void onResult();
        void showAbout();
        void save();
        void print();
        void exportDoc();
        void closeApp();
        void connectToServer();
        void disconnectServer();
        void getContent();
        void freezeContent();
        void tabClose(int index);

    private:
        void createWidgets();
        void createActions();
        void setupMenuBar();

        Ui::MainWindow* m_ui;

        QTabWidget* tabWidget;
        QSplitter* splitter;
        
        ApiCore* api;
        LoginDialog* login;

        QAction* saveAction;
        QAction* printAction;
        QAction* exportAction;
        QAction* exitAction;
        QAction* aboutAction;
        QAction* connectAction;
        QAction* disconnectAction;
    };
}
