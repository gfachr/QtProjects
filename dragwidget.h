#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

//! [0]
class DragWidget : public QFrame
{
public:
    explicit DragWidget(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void simElementPlaced(QLabel *simElement);
};
//! [0]

#endif // DRAGWIDGET_H