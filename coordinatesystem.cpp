#include "coordinatesystem.h"

CoordinateSystem::CoordinateSystem(QWidget *parent)
    : QFrame(parent), iconWidth(100), iconHight(100), cellSize(20), isPanning(false), offset(0, 0), lastMousePos(0, 0)
{
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    setCursor(Qt::ArrowCursor);


}

void CoordinateSystem::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void CoordinateSystem::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void CoordinateSystem::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        JointTypes jointType;
        dataStream >> pixmap >> offset >> jointType;

        Joint *simElement = new Joint(this, jointType);
        simElement->setPixmap(pixmap);
        simElement->move(event->position().toPoint() - offset);
        simElement->show();
        simElement->setAttribute(Qt::WA_DeleteOnClose);
        simElement->setXStart(event->position().toPoint().rx() - offset.rx());
        simElement->setYStart(event->position().toPoint().ry() - offset.ry());

        simElements.push_back(simElement);

        if (event->source() != this) {
            emit this->simElementAdded(simElement);
        }

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            emit this->simElementMoved(simElement);
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

//! [1]
void CoordinateSystem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        isPanning = true;
        lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }

    QLabel *child = static_cast<QLabel*>(childAt(event->position().toPoint()));
    if (!child)
        return;

    QPixmap pixmap = child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->position().toPoint() - child->pos());
    //! [1]

    //! [2]
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);
    //! [2]

    //! [3]
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->position().toPoint() - child->pos());
    //! [3]

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}

void CoordinateSystem::mouseMoveEvent(QMouseEvent *event)
{
    if (isPanning) {
        QPoint delta = event->pos() - lastMousePos;
        offset += delta;
        lastMousePos = event->pos();

        for(Joint* j : simElements) {
            j->setXStart(j->getXStart() + delta.rx());
            j->setYStart(j->getYStart() + delta.ry());
            j->move(j->pos() + delta);
        }

        update();
    }
}

void CoordinateSystem::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        isPanning = false;
        setCursor(Qt::ArrowCursor);
    }
}

void CoordinateSystem::wheelEvent(QWheelEvent  * event) {
    int delta = event->angleDelta().y();
    int zoomStep = 2;

    if (delta > 0 && cellSize < 100) {
        cellSize += zoomStep;
        iconWidth += zoomStep;
        iconHight += zoomStep;
    } else if (delta < 0 && cellSize > 5) {
        cellSize -= zoomStep;
        iconWidth -= zoomStep;
        iconHight -= zoomStep;
    }

    for(Joint* j : simElements) {

        j->resize(iconWidth, iconHight);
    }

    update();
}
void CoordinateSystem::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(QColor(200, 200, 200));

    painter.fillRect(rect(), QColor(255, 255, 255));

    pen.setWidth(1);
    painter.setPen(pen);


    int startX = offset.x() % cellSize;
    int startY = offset.y() % cellSize;

    // Draw vertical grid lines
    for (int x = startX; x < width(); x += cellSize) {
        painter.drawLine(x, 0, x, height());
    }

    // Draw horizontal grid lines
    for (int y = startY; y < height(); y += cellSize) {
        painter.drawLine(0, y, width(), y);
    }
}

//getter and setter

int CoordinateSystem::getCellSize() const
{
    return cellSize;
}

void CoordinateSystem::setCellSize(int newCellSize)
{
    cellSize = newCellSize;
}
