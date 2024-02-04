#pragma once

#include <QMainWindow>
#include <QComboBox>
#include <QToolButton>
#include <QTimer>
#include <QString>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui = nullptr;
    QTimer _clock;

private:
    void init();

protected:
    void keyPressEvent(QKeyEvent *event);

    void closeEvent(QCloseEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);

    void dropEvent(QDropEvent *event);

private slots:

    void load_settings();

    void save_settings();

    void to_main_page();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};