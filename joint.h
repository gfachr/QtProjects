#ifndef JOINT_H
#define JOINT_H

#include <QLabel>
#include "jointTypes.h"

class Joint : public QLabel
{

public:
    explicit Joint(QWidget *parent = nullptr);
    explicit Joint(QWidget *parent = nullptr, JointTypes jointType = fixed);

    double getXStart() const;
    void setXStart(double newXStart);

    double getYStart() const;
    void setYStart(double newYStart);
    double getXSim() const;
    void setXSim(double newXSim);
    double getYSim() const;
    void setYSim(double newYSim);
    double getVxStart() const;
    void setVxStart(double newVxStart);
    double getVyStart() const;
    void setVyStart(double newVyStart);
    double getVxSim() const;
    void setVxSim(double newVxSim);
    double getVySim() const;
    void setVySim(double newVySim);
    double getPhiSim() const;
    void setPhiSim(double newPhiSim);
    double getOmegaSim() const;
    void setOmegaSim(double newOmegaSim);
    double getXForce() const;
    void setXForce(double newXForce);
    double getYForce() const;
    void setYForce(double newYForce);
    bool getIsLocked() const;
    void setIsLocked(bool newIsLocked);
    bool getIsLimited() const;
    void setIsLimited(bool newIsLimited);

    //linJoint
    double getFrictionForceCoefficient() const;
    void setFrictionForceCoefficient(double newFrictionForceCoefficient);
    double getLinStart() const;
    void setLinStart(double newLinStart);
    double getLinEnd() const;
    void setLinEnd(double newLinEnd);
    double getInclinationAngle() const;
    void setInclinationAngle(double newInclinationAngle);
    double getEtaForce() const;
    void setEtaForce(double newEtaForce);
    double getZetaSim() const;
    void setZetaSim(double newZetaSim);

    double getFrictionTorque() const;
    void setFrictionTorque(double newFrictionTorque);
    double getFrictionTorqueCoefficient() const;
    void setFrictionTorqueCoefficient(double newFrictionTorqueCoefficient);
    double getViscousTorqueCoefficient() const;
    void setViscousTorqueCoefficient(double newViscousTorqueCoefficient);
    double getSpringTorqueCoefficient() const;
    void setSpringTorqueCoefficient(double newSpringTorqueCoefficient);
    double getRotationAngleMin() const;
    void setRotationAngleMin(double newRotationAngleMin);
    double getRotationAngleMax() const;
    void setRotationAngleMax(double newRotationAngleMax);

    JointTypes getJointType() const;
    void setJointType(JointTypes newJointType);

private:
    double xStart;
    double yStart;
    double xSim;
    double ySim;

    double vxStart;
    double vyStart;
    double vxSim;
    double vySim;

    double phiSim;
    double omegaSim;

    double xForce;
    double yForce;

    JointTypes jointType;
    bool isLocked;
    bool isLimited;

    //linJoint

    double frictionForceCoefficient;
    double linStart;
    double linEnd;
    double inclinationAngle;
    double etaForce;
    double zetaSim;

    //rotJoint
    double frictionTorque;
    double frictionTorqueCoefficient;
    double viscousTorqueCoefficient;
    double springTorqueCoefficient;
    double rotationAngleMin;
    double rotationAngleMax;

    void updateIcon();


};

#endif // JOINT_H
