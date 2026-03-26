#ifndef BOID_H
#define BOID_H

#include "Vector.h"

#define BOID_DISABLE_ALIGNMENT  (1 << 0)
#define BOID_DISABLE_COHESION   (1 << 1)
#define BOID_DISABLE_SEPARATION (1 << 2)

class CBoid
{

public:
    CBoid(int x, int y, int flags, CBoid* flock, int flockSize);

    Vector align(CBoid* flock, int flockSize);
    Vector separate(CBoid* flock, int flockSize);
    Vector cohese(CBoid* flock, int flockSize);       // cohese isn't a word but for us it is
    void   update(float deltaTime);

    Vector getPosition() const;

private:
    float  m_flMaxSpeed;
    float  m_flMaxForce;
    Vector m_vecVelocity;
    Vector m_vecAcceleration;
    Vector m_vecPosition;
    int    m_iFlags;
    int    m_iPerception2;
    CBoid* m_bdFlock;
    int    m_iFlockSize;
};
#endif