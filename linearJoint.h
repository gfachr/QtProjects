#ifndef LINEARJOINT_H
#define LINEARJOINT_H

#include "joint.h"

class LinearJoint : public Joint
{
public:
    explicit LinearJoint(QWidget *parent = nullptr);
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

private:
    double frictionForceCoefficient;
    double linStart;
    double linEnd;
    double inclinationAngle;
    double etaForce;
    double zetaSim;
};

#endif // LINEARJOINT_H
