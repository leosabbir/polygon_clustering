#include "mainstage.h"

#include <QPainter>
#include <QPolygon>
#include <QPainterPath>
#include <QWidget>

mainstage::mainstage(QWidget *parent) : QWidget(parent)
{
}

void mainstage::paintEvent(QPaintEvent *event) {
    this->draw();
}

void mainstage::draw() {
    QPainter painter(this);

    QPolygon poly;

    poly << QPoint(0, 85) << QPoint(75, 75)
             << QPoint(100, 10) << QPoint(125, 75)
             << QPoint(200, 85) << QPoint(150, 125)
             << QPoint(160, 190) << QPoint(100, 150)
             << QPoint(40, 190) << QPoint(50, 125)
             << QPoint(799, 600) << QPoint(0, 85);

        // QPen: style(), width(), brush(), capStyle() and joinStyle().
        //QPen pen(Qt::red, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawPolygon(poly);
}

