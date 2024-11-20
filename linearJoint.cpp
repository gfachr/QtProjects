#include "linearJoint.h"

LinearJoint::LinearJoint(QWidget *parent)
    :Joint(parent), frictionForceCoefficient(0), linStart(0), linEnd(0), inclinationAngle(0), etaForce(0), zetaSim(0)
{
    xSim = xStart + zetaSim * cos(inclinationAngle);
    ySim = yStart + zetaSim * sin(inclinationAngle);

    setPixmap(QPixmap(":/images/LinSupport.svg").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setScaledContents(true);
    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

double LinearJoint::getFrictionForceCoefficient() const
{
    return frictionForceCoefficient;
}

void LinearJoint::setFrictionForceCoefficient(double newFrictionForceCoefficient)
{
    frictionForceCoefficient = newFrictionForceCoefficient;
}

double LinearJoint::getLinStart() const
{
    return linStart;
}

void LinearJoint::setLinStart(double newLinStart)
{
    linStart = newLinStart;
}

double LinearJoint::getLinEnd() const
{
    return linEnd;
}

void LinearJoint::setLinEnd(double newLinEnd)
{
    linEnd = newLinEnd;
}

double LinearJoint::getInclinationAngle() const
{
    return inclinationAngle;
}

void LinearJoint::setInclinationAngle(double newInclinationAngle)
{
    inclinationAngle = newInclinationAngle;
}

double LinearJoint::getEtaForce() const
{
    return etaForce;
}

void LinearJoint::setEtaForce(double newEtaForce)
{
    etaForce = newEtaForce;
}

double LinearJoint::getZetaSim() const
{
    return zetaSim;
}

void LinearJoint::setZetaSim(double newZetaSim)
{
    zetaSim = newZetaSim;
}
