#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class DragLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DragLabel(QWidget *parent = nullptr);

signals:
    void labelDropped(const QString &msg);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:


};

#endif // DRAGLABEL_H
