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

    private:
        Ui::MainWindow* m_ui;

    };
}
