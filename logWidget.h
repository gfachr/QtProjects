#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QtWidgets>
#include <QPlainTextEdit>
#include "joint.h"

class LogWidget : public QFrame
{

    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = nullptr);

public slots:
    void appendElementAddInfo(Joint *simElement);
    void appendElementMovedInfo(Joint *simElement);
private:
    QPlainTextEdit *plainTextEdit;
};
#endif // LOGWIDGET_H
