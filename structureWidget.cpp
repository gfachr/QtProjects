#include <QtWidgets>
#include <QHBoxLayout>
#include "structureWidget.h"

StructureWidget::StructureWidget(QWidget *parent)
    : QFrame(parent), simStructure(new QTreeWidget(this))
{
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(simStructure);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    simStructure->setColumnCount(1);

}

void StructureWidget::addVertex(Joint *simElement) {
    QTreeWidgetItem *item = new QTreeWidgetItem(simStructure);
    item->setText(0, tr("New Vertex"));
    simStructure->insertTopLevelItem(0, item);
}
