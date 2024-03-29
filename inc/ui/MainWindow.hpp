#pragma once

#include <QMainWindow>
#include <QComboBox>
#include <QToolButton>
#include <QTimer>
#include <QString>
#include <QStringListModel>



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
    QStringList _files, _original_names;
    QStringListModel _file_model;

private:
    void init();

private slots:
    void degree_to_rad(double value);

    void rad_to_degree(double value);

    void open_files();

    void open_folder();

    void rename_files();

    void undo_rename();

    void clear_files();

    void reset();

    void filter_files();

protected:


    void closeEvent(QCloseEvent *event);


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};