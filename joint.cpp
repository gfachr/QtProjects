#include "joint.h"

Joint::Joint(QWidget *parent)
    : QLabel(parent), xStart(0), yStart(0), xSim(0), ySim(0), vxStart(0), vyStart(0), vxSim(0), vySim(0),
    phiSim(0), omegaSim(0), xForce(0), yForce(0), isLocked(false), isLimited(false),
    frictionForceCoefficient(0), linStart(0), linEnd(0), inclinationAngle(0), etaForce(0), zetaSim(0) {}

Joint::Joint(QWidget *parent, JointTypes jointType)
    : QLabel(parent), xStart(0), yStart(0), xSim(0), ySim(0), vxStart(0), vyStart(0), vxSim(0), vySim(0),
    phiSim(0), omegaSim(0), xForce(0), yForce(0), isLocked(false), isLimited(false),
    frictionForceCoefficient(0), linStart(0), linEnd(0), inclinationAngle(0), etaForce(0), zetaSim(0)
{
    setJointType(jointType);
    xSim = xStart + zetaSim * cos(inclinationAngle);
    ySim = yStart + zetaSim * sin(inclinationAngle);
    updateIcon();
}

void Joint::updateIcon() {
    if (jointType == fixed) {
        setPixmap(QPixmap(":/images/FixedSupport.svg").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        setScaledContents(true);
        show();
        setAttribute(Qt::WA_DeleteOnClose);
    }
    else if (jointType == linear) {
        setPixmap(QPixmap(":/images/LinSupport.svg").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        setScaledContents(true);
        show();
        setAttribute(Qt::WA_DeleteOnClose);
    }
    else if (jointType == guided) {
        setPixmap(QPixmap(":/images/VarSupport.svg").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        setScaledContents(true);
        show();
        setAttribute(Qt::WA_DeleteOnClose);
    }
}


//getter and setter

double Joint::getXStart() const
{
    return xStart;
}

void Joint::setXStart(double newXStart)
{
    xStart = newXStart;
}

double Joint::getYStart() const
{
    return yStart;
}

void Joint::setYStart(double newYStart)
{
    yStart = newYStart;
}

double Joint::getXSim() const
{
    return xSim;
}

void Joint::setXSim(double newXSim)
{
    xSim = newXSim;
}

double Joint::getYSim() const
{
    return ySim;
}

void Joint::setYSim(double newYSim)
{
    ySim = newYSim;
}

double Joint::getVxStart() const
{
    return vxStart;
}

void Joint::setVxStart(double newVxStart)
{
    vxStart = newVxStart;
}

double Joint::getVyStart() const
{
    return vyStart;
}

void Joint::setVyStart(double newVyStart)
{
    vyStart = newVyStart;
}

double Joint::getVxSim() const
{
    return vxSim;
}

void Joint::setVxSim(double newVxSim)
{
    vxSim = newVxSim;
}

double Joint::getVySim() const
{
    return vySim;
}

void Joint::setVySim(double newVySim)
{
    vySim = newVySim;
}

double Joint::getPhiSim() const
{
    return phiSim;
}

void Joint::setPhiSim(double newPhiSim)
{
    phiSim = newPhiSim;
}

double Joint::getOmegaSim() const
{
    return omegaSim;
}

void Joint::setOmegaSim(double newOmegaSim)
{
    omegaSim = newOmegaSim;
}

double Joint::getXForce() const
{
    return xForce;
}

void Joint::setXForce(double newXForce)
{
    xForce = newXForce;
}

double Joint::getYForce() const
{
    return yForce;
}

void Joint::setYForce(double newYForce)
{
    yForce = newYForce;
}

bool Joint::getIsLocked() const
{
    return isLocked;
}

void Joint::setIsLocked(bool newIsLocked)
{
    isLocked = newIsLocked;
}

bool Joint::getIsLimited() const
{
    return isLimited;
}

void Joint::setIsLimited(bool newIsLimited)
{
    isLimited = newIsLimited;
}

//linJoint

double Joint::getFrictionForceCoefficient() const
{
    return frictionForceCoefficient;
}

void Joint::setFrictionForceCoefficient(double newFrictionForceCoefficient)
{
    frictionForceCoefficient = newFrictionForceCoefficient;
}

double Joint::getLinStart() const
{
    return linStart;
}

void Joint::setLinStart(double newLinStart)
{
    linStart = newLinStart;
}

double Joint::getLinEnd() const
{
    return linEnd;
}

void Joint::setLinEnd(double newLinEnd)
{
    linEnd = newLinEnd;
}

double Joint::getInclinationAngle() const
{
    return inclinationAngle;
}

void Joint::setInclinationAngle(double newInclinationAngle)
{
    inclinationAngle = newInclinationAngle;
}

double Joint::getEtaForce() const
{
    return etaForce;
}

void Joint::setEtaForce(double newEtaForce)
{
    etaForce = newEtaForce;
}

double Joint::getZetaSim() const
{
    return zetaSim;
}

void Joint::setZetaSim(double newZetaSim)
{
    zetaSim = newZetaSim;
}

double Joint::getFrictionTorque() const
{
    return frictionTorque;
}

void Joint::setFrictionTorque(double newFrictionTorque)
{
    frictionTorque = newFrictionTorque;
}

double Joint::getFrictionTorqueCoefficient() const
{
    return frictionTorqueCoefficient;
}

void Joint::setFrictionTorqueCoefficient(double newFrictionTorqueCoefficient)
{
    frictionTorqueCoefficient = newFrictionTorqueCoefficient;
}

double Joint::getViscousTorqueCoefficient() const
{
    return viscousTorqueCoefficient;
}

void Joint::setViscousTorqueCoefficient(double newViscousTorqueCoefficient)
{
    viscousTorqueCoefficient = newViscousTorqueCoefficient;
}

double Joint::getSpringTorqueCoefficient() const
{
    return springTorqueCoefficient;
}

void Joint::setSpringTorqueCoefficient(double newSpringTorqueCoefficient)
{
    springTorqueCoefficient = newSpringTorqueCoefficient;
}

double Joint::getRotationAngleMin() const
{
    return rotationAngleMin;
}

void Joint::setRotationAngleMin(double newRotationAngleMin)
{
    rotationAngleMin = newRotationAngleMin;
}

double Joint::getRotationAngleMax() const
{
    return rotationAngleMax;
}

void Joint::setRotationAngleMax(double newRotationAngleMax)
{
    rotationAngleMax = newRotationAngleMax;
}

JointTypes Joint::getJointType() const
{
    return jointType;
}

void Joint::setJointType(JointTypes newJointType)
{
    jointType = newJointType;
}
