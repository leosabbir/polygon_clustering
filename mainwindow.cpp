#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "context.h"
#include "constants.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->initializeEditModes();
    ui->thresholdSlider->setValue(Constants::INITIAL_THRESHOLD);
    ui->threshHoldLbl->setText(QString::number(Constants::INITIAL_THRESHOLD));
    ui->applyBtn->setEnabled(false);

    connect(ui->maincontainer, SIGNAL(hadMousePress(int, int)), this, SLOT(onMouseEvent(int, int)));
    connect(ui->maincontainer, SIGNAL(hadMouseMove(int, int)), this, SLOT(onMouseMoveEvent(int, int)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initializeEditModes() {
    this->ui->editModeComboBox->addItem("Normal");
    this->ui->editModeComboBox->addItem("Edit");
    this->ui->editModeComboBox->addItem("Add Vertex");
    this->ui->editModeComboBox->addItem("Delete Vertex");

    this->ui->editModeComboBox->setCurrentIndex(0);
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

void MainWindow::onMouseEvent(int x, int y) {
    ui->maincontainer->paintGL();
    ui->maincontainer->update();
}

void MainWindow::onMouseMoveEvent(int x, int y) {
}

void MainWindow::on_editModeComboBox_currentIndexChanged(int index) {
    Context::getInstance()->setEditMode(index);
}
