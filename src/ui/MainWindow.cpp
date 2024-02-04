#include "ui/MainWindow.hpp"
#include "./ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QAbstractItemView>
#include <QMimeData>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _setting(new Setting(this)),
    _panel(new DataPanel(this))
{
    ui->setupUi(this);
    init();
    load_settings();
}

MainWindow::~MainWindow()
{
    save_settings();
    delete ui;
}

void MainWindow::init()
{
    setAcceptDrops(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}





void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QString suffixs = "dsv DSV pdf PDF plt PLT cut CUT";
    QFileInfo file_info(event->mimeData()->urls().front().toLocalFile());
    if( file_info.isFile() && suffixs.contains(file_info.suffix()))
    {
        open_file(file_info.absoluteFilePath());
    }
}


void MainWindow::load_settings()
{   
    GlobalSetting::get_instance()->load_setting();
    const QJsonObject &setting = GlobalSetting::get_instance()->setting();

    _editer.set_path(setting["file_path"].toString());
    ui->auto_save->setChecked(setting["auto_save"].toBool());
    ui->auto_layering->setChecked(setting["auto_layering"].toBool());
    ui->auto_aligning->setChecked(setting["auto_aligning"].toBool());
    ui->remember_file_type->setChecked(setting["remember_file_type"].toBool());
    ui->show_cmd_line->setChecked(setting["show_cmd_line"].toBool());
    ui->show_origin->setChecked(setting["show_origin"].toBool());
    if (ui->show_cmd_line->isChecked())
    {
        _cmd_widget->show();
    }
    else
    {
        _cmd_widget->hide();
    }
    if (ui->show_origin->isChecked())
    {
        _painter.show_origin();
    }
    else
    {
        _painter.hide_origin();
    }
    if (ui->remember_file_type->isChecked())
    {
       _file_type = setting["file_type"].toString();
    }
}

void MainWindow::save_settings()
{
    QJsonObject &setting = GlobalSetting::get_instance()->setting();

    setting["auto_save"] = ui->auto_save->isChecked();
    setting["auto_layering"] = ui->auto_layering->isChecked();
    setting["auto_aligning"] = ui->auto_aligning->isChecked();
    setting["remember_file_type"] = ui->remember_file_type->isChecked();
    setting["show_cmd_line"] = ui->show_cmd_line->isChecked();
    setting["show_origin"] = ui->show_origin->isChecked();
    if (ui->remember_file_type->isChecked())
    {
        setting["file_type"] = _file_type;
    }

    GlobalSetting::get_instance()->save_setting();
}

void MainWindow::to_main_page()
{
    ui->tool_widget->setCurrentIndex(0);
}

