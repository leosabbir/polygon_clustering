#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "context.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    int initialThreshold = 100;
    ui->thresholdSlider->setValue(initialThreshold);
    ui->threshHoldLbl->setText(QString::number(initialThreshold));
    ui->applyBtn->setEnabled(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_thresholdSlider_sliderMoved(int position) {
    ui->threshHoldLbl->setText(QString::number(position));
    ui->applyBtn->setEnabled(true);
}

void MainWindow::on_thresholdSlider_valueChanged(int value) {
    ui->threshHoldLbl->setText(QString::number(value));
    ui->applyBtn->setEnabled(true);
}

void MainWindow::on_applyBtn_released() {
    ui->applyBtn->setEnabled(false);
    Context::getInstance()->reComputeConnectingLines(ui->thresholdSlider->value());
    ui->maincontainer->paintGL();
    ui->maincontainer->update();
}
