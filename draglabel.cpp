#include "draglabel.h"

DraggableLabel::DraggableLabel(QWidget *parent)
    : QLabel(parent)
{
    setAcceptDrops(true);
}

void DraggableLabel::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void DraggableLabel::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasText()) {
        QString droppedText = event->mimeData()->text();
        emit iconDropped(droppedText);
        event->acceptProposedAction();
    }
}
