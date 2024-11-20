#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include <QtWidgets>
#include "joint.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class CoordinateSystem : public QFrame
{

    Q_OBJECT

public:
    explicit CoordinateSystem(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void simElementAdded(Joint *simElement);
    void simElementMoved(Joint *simElement);
};

#endif // COORDINATESYSTEM_H

