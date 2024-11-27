#include <QVBoxLayout>
#include "logWidget.h"

LogWidget::LogWidget(QWidget *parent)
    : QFrame(parent), plainTextEdit(new QPlainTextEdit(this))
{
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);

    plainTextEdit->setReadOnly(true);
    QFont font("Courier", 10);
    plainTextEdit->setFont(font);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(plainTextEdit);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    QString text = "Mechanism - V0.0";
    plainTextEdit->appendPlainText(text);

}

void LogWidget::appendElementAddInfo(Joint *simElement) {
    double x = simElement->getXStart();
    double y = simElement->getYStart();
    QString simElementId = simElement->getUuid().toString(QUuid::WithBraces);
    QString msg = QString("New Simulation component with Id=%1 place at x =%2 and y =%3").arg(simElementId).arg(x).arg(y);
    plainTextEdit->appendPlainText(msg);
}

void LogWidget::appendElementMovedInfo(Joint *simElement) {
    double x = simElement->getXStart();
    double y = simElement->getYStart();
    QString simElementId = simElement->getUuid().toString(QUuid::WithBraces);
    QString msg = QString("Simulation component with Id=%1 moved to x =%2 and y =%3").arg(simElementId).arg(x).arg(y);
    plainTextEdit->appendPlainText(msg);
}
