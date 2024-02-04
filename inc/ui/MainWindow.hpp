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

    bool _angle_changed = true;

private:
    void init();

private slots:
    void degree_to_rad(double value);

    void rad_to_degree(double value);

protected:


    void closeEvent(QCloseEvent *event);


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};