#include "ui/MainWindow.hpp"
#include "./ui_MainWindow.h"
#include "math/Math.hpp"
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



void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}











