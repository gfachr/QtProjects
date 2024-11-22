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

    int getCellSize() const;
    void setCellSize(int newCellSize);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent  * event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    int iconWidth;
    int iconHight;
    int cellSize;
    bool isPanning;
    QPoint offset;
    QPoint lastMousePos;
    std::vector<Joint*> simElements;

signals:
    void simElementAdded(Joint *simElement);
    void simElementMoved(Joint *simElement);
};

#endif // COORDINATESYSTEM_H

