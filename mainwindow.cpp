#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "context.h"
#include "constants.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->initializeEditModes();
    ui->thresholdSlider->setValue(Constants::INITIAL_THRESHOLD);
    ui->threshHoldLbl->setText(QString::number(Constants::INITIAL_THRESHOLD));
    ui->applyBtn->setEnabled(false);

    connect(ui->maincontainer, SIGNAL(hadMousePress(int, int, bool)), this, SLOT(onMouseEvent(int, int, bool)));
    connect(ui->maincontainer, SIGNAL(hadMouseMove(int, int)), this, SLOT(onMouseMoveEvent(int, int)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initializeEditModes() {
    this->ui->algoMode->addItem("Add Polygon");
    this->ui->algoMode->addItem("Nearest Neighbour");
    this->ui->algoMode->addItem("K-means");
    this->ui->algoMode->addItem("Voronoi");
    this->ui->algoMode->setCurrentIndex(0);
    this->adaptSelectedAlgorithmMode(0);

    this->ui->editModeComboBox->addItem("Normal");
    this->ui->editModeComboBox->addItem("Edit");
    this->ui->editModeComboBox->addItem("Add Vertex");
    this->ui->editModeComboBox->addItem("Delete Vertex");
    this->ui->editModeComboBox->addItem("Move Polygon");

    this->ui->editModeComboBox->setCurrentIndex(0);
}


void MainWindow::adaptSelectedAlgorithmMode(int index) {
    switch(index) {
        case 0: // create polygons
            this->ui->createBtn->setVisible(true);
            this->ui->editModeComboBox->setVisible(true);
            this->ui->editModeLbl->setVisible(true);

            this->ui->thresholdTtle->setVisible(false);
            this->ui->threshHoldLbl->setVisible(false);
            this->ui->thresholdSlider->setVisible(false);
            this->ui->applyBtn->setVisible(false);

            this->ui->borderChkBox->setVisible(false);
            this->ui->verticesChkBox->setVisible(false);
            this->ui->showAllEdgesChkBox->setVisible(false);

            return;
        case 1: // apply nearest neighbour
            this->ui->createBtn->setVisible(false);
            this->ui->editModeComboBox->setVisible(false);
            this->ui->editModeLbl->setVisible(false);

            this->ui->thresholdTtle->setVisible(true);
            this->ui->threshHoldLbl->setVisible(true);
            this->ui->thresholdSlider->setVisible(true);
            this->ui->applyBtn->setVisible(true);

            this->ui->borderChkBox->setVisible(false);
            this->ui->verticesChkBox->setVisible(false);
            this->ui->showAllEdgesChkBox->setVisible(false);
            return;
        case 2: // apply k-means
            this->ui->createBtn->setVisible(false);
            this->ui->editModeComboBox->setVisible(false);
            this->ui->editModeLbl->setVisible(false);

            this->ui->thresholdTtle->setVisible(false);
            this->ui->threshHoldLbl->setVisible(false);
            this->ui->thresholdSlider->setVisible(false);
            this->ui->applyBtn->setVisible(false);

            this->ui->borderChkBox->setVisible(true);
            this->ui->verticesChkBox->setVisible(true);
            this->ui->showAllEdgesChkBox->setVisible(false);

            Context::getInstance()->setDrawVoronoi(false);
            return;
        default: // apply voronoi
            this->ui->createBtn->setVisible(false);
            this->ui->editModeComboBox->setVisible(false);
            this->ui->editModeLbl->setVisible(false);

            this->ui->thresholdTtle->setVisible(false);
            this->ui->threshHoldLbl->setVisible(false);
            this->ui->thresholdSlider->setVisible(false);
            this->ui->applyBtn->setVisible(false);

            this->ui->borderChkBox->setVisible(true);
            this->ui->verticesChkBox->setVisible(true);
            this->ui->showAllEdgesChkBox->setVisible(true);

            Context::getInstance()->setDrawVoronoi(true);
            return;
    }

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
    Context::getInstance()->setDrawConnectingLines(true);
    Context::getInstance()->reComputeConnectingLines(ui->thresholdSlider->value());
    ui->maincontainer->paintGL();
    ui->maincontainer->update();
}

void MainWindow::onMouseEvent(int x, int y, bool disableConnectingLines) {
    if (disableConnectingLines) {
        ui->applyBtn->setEnabled(true);
    }
    ui->maincontainer->paintGL();
    ui->maincontainer->update();
}

void MainWindow::onMouseMoveEvent(int x, int y) {
    ui->applyBtn->setEnabled(true);
}

void MainWindow::on_editModeComboBox_currentIndexChanged(int index) {
    Context::getInstance()->setEditMode(index);
}

void MainWindow::on_createBtn_released() {
    if (Context::getInstance()->getEditMode() == Constants::CREATE_POLYGONS_MODE) {
        this->ui->createBtn->setText("Create");
        Context::getInstance()->setEditMode(this->ui->editModeComboBox->currentIndex());
        this->ui->applyBtn->setEnabled(true);
        this->ui->editModeComboBox->setEnabled(true);
        this->ui->thresholdSlider->setEnabled(true);
    } else {
        Context::getInstance()->setEditMode(Constants::CREATE_POLYGONS_MODE);
        this->ui->createBtn->setText("Done");
        this->ui->applyBtn->setEnabled(false);
        this->ui->editModeComboBox->setEnabled(false);
        this->ui->thresholdSlider->setEnabled(false);
    }
}

void MainWindow::on_openBtn_released() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ":/resources/", "All files (*.*);;Text File(*.txt)");
    if(fileName.isEmpty()) {
        return;
    }
    Context::getInstance()->getFileReader().loadPolygons(fileName);
    Context::getInstance()->setDrawConnectingLines(false);
    this->ui->maincontainer->paintGL();
    this->ui->maincontainer->update();
}

void MainWindow::on_saveBtn_released() {
    Context::getInstance()->getFileReader().savePolygons();
}

void MainWindow::on_saveasBtn_released() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), ":/resources/", "All files (*.*);;Text File(*.txt)");
    if(fileName.isEmpty()) {
        return;
    }
    Context::getInstance()->getFileReader().savePolygons(fileName);
}

void MainWindow::on_clearBtn_released() {
    Context::getInstance()->getFileReader().clear();
    Context::getInstance()->setDrawConnectingLines(false);
    this->ui->maincontainer->paintGL();
    this->ui->maincontainer->update();
}

void MainWindow::on_borderChkBox_released() {
    Context::getInstance()->setBorderEnabled(this->ui->borderChkBox->checkState() == Qt::Checked);
    this->ui->maincontainer->paintGL();
    this->ui->maincontainer->update();
}

void MainWindow::on_verticesChkBox_released() {
    Context::getInstance()->setVerticesEnabled(this->ui->verticesChkBox->checkState() == Qt::Checked);
    if (!Context::getInstance()->isVerticesEnabled()) {
        this->ui->showAllEdgesChkBox->setChecked(false);
        this->ui->showAllEdgesChkBox->setEnabled(false);
    } else {
        Context::getInstance()->setDrawOnlyNonIntersectingVoronoiEdges(true);
        this->ui->showAllEdgesChkBox->setChecked(true);
        this->ui->showAllEdgesChkBox->setEnabled(true);
    }
    this->ui->maincontainer->paintGL();
    this->ui->maincontainer->update();
}

void MainWindow::on_showAllEdgesChkBox_released() {
    if (Context::getInstance()->isVerticesEnabled()) {
        Context::getInstance()->setDrawOnlyNonIntersectingVoronoiEdges(this->ui->showAllEdgesChkBox->checkState() == Qt::Checked);
        this->ui->maincontainer->paintGL();
        this->ui->maincontainer->update();
    }
}

void MainWindow::on_xfigFileBtn_released() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), ":/resources/", "All files (*.*);;Text File(*.txt)");
    if(fileName.isEmpty()) {
        return;
    }
    this->ui->maincontainer->generateXfigFile(fileName);
}

void MainWindow::on_algoMode_currentIndexChanged(int index) {
    Context::getInstance()->setDrawConnectingLines(false);

    this->ui->borderChkBox->setChecked(true);
    Context::getInstance()->setBorderEnabled(true);
    this->ui->verticesChkBox->setChecked(false);
    Context::getInstance()->setVerticesEnabled(false);
    this->ui->showAllEdgesChkBox->setChecked(false);

    this->adaptSelectedAlgorithmMode(index);
    this->ui->maincontainer->paintGL();
    this->ui->maincontainer->update();
}
