#ifndef STRUCTUREWIDGET_H
#define STRUCTUREWIDGET_H


#include <QtWidgets>
#include "joint.h"

class StructureWidget : public QFrame
{
public:
    explicit StructureWidget(QWidget *parent = nullptr);

public slots:
    void addVertex(Joint *simElement);

private:
    QTreeWidget *simStructure;
};

#endif // STRUCTUREWIDGET_H
