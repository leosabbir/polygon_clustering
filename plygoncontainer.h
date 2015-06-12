#ifndef PLYGONCONTAINER_H
#define PLYGONCONTAINER_H

#include <QWidget>

namespace Ui {
class PlygonContainer;
}

class PlygonContainer : public QWidget
{
    Q_OBJECT

public:
    explicit PlygonContainer(QWidget *parent = 0);
    ~PlygonContainer();

private:
    Ui::PlygonContainer *ui;
};

#endif // PLYGONCONTAINER_H
