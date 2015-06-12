#include "plygoncontainer.h"
#include "ui_plygoncontainer.h"


PlygonContainer::PlygonContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlygonContainer)
{
    ui->setupUi(this);

}

PlygonContainer::~PlygonContainer()
{
    delete ui;
}
