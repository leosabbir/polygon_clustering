#ifndef MAINSTAGE_H
#define MAINSTAGE_H

#include <QWidget>

class mainstage : public QWidget
{
    Q_OBJECT
public:
    explicit mainstage(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void draw();
signals:

public slots:
};

#endif // MAINSTAGE_H
