#include "coordinatesystem.h"

CoordinateSystem::CoordinateSystem(QWidget *parent)
    : QFrame(parent), iconWidth(100), iconHight(100), scaleFactor(1), cellSize(20), offset(0, 0), lastMousePos(0, 0)
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
    } else if (event->mimeData()->hasFormat("application/x-object-pointer")) {
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
            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();
            } else {
                event->acceptProposedAction();
            }
        }
    } else if (event->mimeData()->hasFormat("application/x-object-pointer")) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void CoordinateSystem::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         if (event->source() != this) {
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
            simElement->setAttribute(Qt::WA_DeleteOnClose, false);
            simElement->setXStart(event->position().toPoint().rx() - offset.rx());
            simElement->setYStart(event->position().toPoint().ry() - offset.ry());

            simElements.push_back(simElement);
            emit this->simElementAdded(simElement);
        }

    } else if (event->mimeData()->hasFormat("application/x-object-pointer")) {

        QByteArray pointerData = event->mimeData()->data("application/x-object-pointer");
        Joint *joint = reinterpret_cast<Joint *>(pointerData.toULongLong());

        if (joint) {
            joint->setParent(this);
            joint->move(event->position().toPoint() - joint->getDragDropOffset());
            joint->setXStart(event->position().toPoint().rx() - joint->getDragDropOffset().rx());
            joint->setYStart(event->position().toPoint().ry() - joint->getDragDropOffset().ry());
            joint->show();
            emit this->simElementMoved(joint);
        }
        event->acceptProposedAction();

    } else {
        event->ignore();
    }
}

//! [1]
void CoordinateSystem::mousePressEvent(QMouseEvent *event)
{
    //handle mouse events
    if (event->button() == Qt::MiddleButton) {
        isPanning = true;
        lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    else if (event->button() == Qt::LeftButton) {
        Joint *child = static_cast<Joint*>(childAt(event->position().toPoint()));
        if (!child) {
            return;
        }
        child->setDragDropOffset(QPoint(event->position().toPoint() - child->pos()));
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        mimeData->setData("application/x-object-pointer", QByteArray::number(reinterpret_cast<quintptr>(child)));

        drag->setMimeData(mimeData);
        drag->setPixmap(child->pixmap());
        drag->setHotSpot(event->position().toPoint() - child->pos());
        drag->exec(Qt::MoveAction);
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
    double zoomFctor = 1.05;

    if (delta > 0) {
        scaleFactor *= zoomFctor;
    } else if (delta < 0) {
        scaleFactor /= zoomFctor;
    }

    for(Joint* j : simElements) {
        QPoint pos = j->pos();
        j->resize(iconWidth*scaleFactor, iconHight*scaleFactor);
        j->move(pos.rx(), pos.ry());
    }

    update();
}
void CoordinateSystem::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    QTransform transform = painter.transform();
    painter.setRenderHint(QPainter::Antialiasing);
    //painter.fillRect(event->rect(), QBrush(Qt::white));
    QRect rect(0, 0, width(), height());
    painter.fillRect(rect, QBrush(Qt::white));


    QPen pen(QColor(200, 200, 200));
    pen.setWidth(1);
    painter.setPen(pen);

    transform.translate((width()/2), (height()/2));
    transform.scale(scaleFactor, scaleFactor);
    painter.setWorldTransform(transform);

    // Draw vertical grid lines
    for (int x = cellSize/2; x < (1/scaleFactor)*width()/2; x += cellSize) {
        painter.drawLine(x, -(1/scaleFactor)*height()/2, x, (1/scaleFactor)*height()/2);
    }

    for (int x = -cellSize/2; x > -(1/scaleFactor)*width()/2; x -= cellSize) {
       painter.drawLine(x, -(1/scaleFactor)*height()/2, x, (1/scaleFactor)*height()/2);
    }

    // Draw horizontal grid lines
    for (int y = cellSize/2; y < (1/scaleFactor)*height()/2; y += cellSize) {
        painter.drawLine(-(1/scaleFactor)*width()/2, y, (1/scaleFactor)*width()/2, y);
    }

    for (int y = -cellSize/2; y > -(1/scaleFactor)*height()/2; y -= cellSize) {
       painter.drawLine(-(1/scaleFactor)*width()/2, y, (1/scaleFactor)*width()/2, y);
    }

    pen.setColor(QColor(0, 0, 0));
    painter.setPen(pen);
    pen.setWidth(2);
    painter.drawLine(0, -(1/scaleFactor)*height()/2, 0, (1/scaleFactor)*height()/2);
    painter.drawLine(-(1/scaleFactor)*width()/2, 0, (1/scaleFactor)*width()/2, 0);

    const QPoint origin = QPoint(0, 0);
    QPixmap pixmap = QPixmap(":/images/FixedSupport.svg").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(origin, pixmap);



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
