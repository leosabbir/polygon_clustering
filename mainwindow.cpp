#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "context.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    int initialThreshold = 100;
    ui->thresholdSlider->setValue(initialThreshold);
    ui->threshHoldLbl->setText(QString::number(initialThreshold));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_thresholdSlider_sliderMoved(int position) {
    ui->threshHoldLbl->setText(QString::number(position));
}

void MainWindow::on_thresholdSlider_valueChanged(int value) {
    ui->threshHoldLbl->setText(QString::number(value));
}

void MainWindow::on_applyBtn_released() {
    Context::getInstance()->reComputeConnectingLines(ui->thresholdSlider->value());
}
