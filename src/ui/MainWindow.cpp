#include "ui/MainWindow.hpp"
#include "./ui_MainWindow.h"
#include "math/Math.hpp"
#include "file/File.hpp"
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QAbstractItemView>
#include <QMimeData>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    QStringList items;
    items << "Back" << "Front";
    ui->file_order_place->addItems(items);

    ui->file_list->setModel(&_file_model);
}


void MainWindow::degree_to_rad(double value)
{
    value = PI * value / 180.0;
    ui->angle_rad->blockSignals(true);
    ui->angle_rad->setValue(value);
    ui->angle_rad->blockSignals(false);

    ui->sin_value->setText(QString::number(std::sin(value), 103, 8));
    ui->cos_value->setText(QString::number(std::cos(value), 103, 8));
    ui->tan_value->setText(QString::number(std::tan(value), 103, 8));

    ui->csc_value->setText(QString::number(1.0 / std::sin(value), 103, 8));
    ui->sec_value->setText(QString::number(1.0 / std::cos(value), 103, 8));
    ui->cot_value->setText(QString::number(1.0 / std::tan(value), 103, 8));
}

void MainWindow::rad_to_degree(double value)
{
    ui->angle_degree->blockSignals(true);
    ui->angle_degree->setValue(180.0 * value / PI);
    ui->angle_degree->blockSignals(false);

    ui->sin_value->setText(QString::number(std::sin(value), 103, 8));
    ui->cos_value->setText(QString::number(std::cos(value), 103, 8));
    ui->tan_value->setText(QString::number(std::tan(value), 103, 8));

    ui->csc_value->setText(QString::number(1.0 / std::sin(value), 103, 8));
    ui->sec_value->setText(QString::number(1.0 / std::cos(value), 103, 8));
    ui->cot_value->setText(QString::number(1.0 / std::tan(value), 103, 8));
}

void MainWindow::open_files()
{
    _files = QFileDialog::getOpenFileNames(this);
    if (_files.isEmpty())
    {
        _file_model.setStringList(_files);
        return;
    }
    QStringList names;
    for (const QString &file : _files)
    {
        names.append(QFileInfo(file).fileName());
    }
    _original_names = names;
    _file_model.setStringList(names);
}

void MainWindow::open_folder()
{
    QString path = QFileDialog::getExistingDirectory(this);
    if (path.isEmpty())
    {
        _file_model.setStringList(_files);
        return;
    }
    QStringList names;
    for (const QString &file : QDir(path).entryList(QDir::Filter::Files))
    {
        names.append(file);
        _files.append(path + '/' + file);
    }
    _original_names = names;
    _file_model.setStringList(names);
}

void MainWindow::rename_files()
{
    FileTool::RenameRule rule;
    rule.name = ui->file_name->text();
    if (ui->file_name_keep->isChecked())
    {
        rule.upper = FileTool::UpperOrLower::Keep;
    }
    else if (ui->file_name_upper->isChecked())
    {
        rule.upper = FileTool::UpperOrLower::Upper;
    }
    else
    {
        rule.upper = FileTool::UpperOrLower::Lower;
    }
    rule.remove = ui->file_remove->text();
    rule.prefix = ui->file_prefix->text();
    rule.suffix = ui->file_suffix->text();
    rule.remove_from = ui->file_remove_from->text();
    rule.remove_to = ui->file_remove_to->text();
    rule.replace_src = ui->file_name_replace_src->text();
    rule.replace_dst = ui->file_name_replace_dst->text();
    rule.no_space = ui->file_remove_space->isChecked();
    rule.add_order = ui->file_add_order->isChecked();
    rule.fix_order_length = ui->file_fix_order_len->isChecked();
    switch (ui->file_order_place->currentIndex())
    {
    case 0:
        rule.order_place = FileTool::OrderPlace::Back;
        break;
    case 1:
        rule.order_place = FileTool::OrderPlace::Front;
        break;
    default:
        break;
    }
    rule.order = ui->file_order_begin->value();
    rule.order_step = ui->file_order_step->value();
    rule.order_prefix = ui->file_order_prefix->text();
    rule.order_suffix = ui->file_order_suffix->text();
    
    FileTool::rename_file(_files, rule);
    QStringList names;
    for (const QString &file : _files)
    {
        names.append(QFileInfo(file).fileName());
    }
    _file_model.setStringList(names);
}

void MainWindow::undo_rename()
{
    FileTool::rename_file(_files, _original_names);
    _file_model.setStringList(_original_names);
}

void MainWindow::clear_files()
{
    _files.clear();
    _file_model.setStringList(_files);
}

void MainWindow::reset()
{
    ui->file_name->clear();
    ui->file_remove->clear();
    ui->file_prefix->clear();
    ui->file_suffix->clear();
    ui->file_remove_from->clear();
    ui->file_remove_to->clear();
    ui->file_name_replace_src->clear();
    ui->file_name_replace_dst->clear();
    ui->file_remove_space->setChecked(false);

    ui->file_add_order->setChecked(false);
    ui->file_fix_order_len->setChecked(true);
    ui->file_order_place->setCurrentIndex(0);
    ui->file_order_begin->setValue(0);
    ui->file_order_step->setValue(1);
    ui->file_order_prefix->clear();
    ui->file_order_suffix->clear();
    ui->file_name_keep->setChecked(true);
}

void MainWindow::filter_files()
{
    const QString suffix = ui->file_filter->text();
    QStringList names;
    for (size_t i = 0, count = _files.size(); i < count; ++i)
    {
        if (_files[i].endsWith(suffix))
        {
            names.append(QFileInfo(_files[i]).fileName());
        }
        else
        {
            _original_names.removeAt(i);
            _files.removeAt(i--);
            --count;
        }
    }
    _file_model.setStringList(names);
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}











