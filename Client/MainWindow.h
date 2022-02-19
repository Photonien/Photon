#include <QMainWindow>

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

    private:
        void createActions();
        void setupMenuBar();

        Ui::MainWindow* m_ui;
        
        QAction* saveAction;
        QAction* printAction;
        QAction* exportAction;
        QAction* exitAction;
        QAction* aboutAction;
        QAction* connectAction;
        QAction* disconnectAction;

    };
}
