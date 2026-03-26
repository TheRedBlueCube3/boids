#include "Boid.h"
#include "utils.h"

CBoid::CBoid( int p_x, int p_y, int p_flags, CBoid* p_flock, int p_flockSize )
: m_vecPosition( p_x, p_y ),
  m_vecVelocity( g_vecZero ),
  m_vecAcceleration( g_vecZero ),
  m_iFlags( p_flags & 0b111 ),
  m_flMaxForce( 100.0f ),
  m_flMaxSpeed( 200.0f ),
  m_iPerception2( 625 ),
  m_bdFlock( p_flock ), 
  m_iFlockSize( p_flockSize )
{

}

void CBoid::update( float p_deltaTime )
{
    Vector alignment = align( m_bdFlock, m_iFlockSize );
    Vector separation = separate( m_bdFlock, m_iFlockSize );
    Vector cohesion = cohese( m_bdFlock, m_iFlockSize );
    // redundant
    // m_vecAcceleration = g_vecZero;
    m_vecAcceleration = alignment + separation + cohesion;
    m_vecAcceleration = m_vecAcceleration.limit( m_flMaxForce ); // limiting instead of setting magnitude is important here
    m_vecVelocity += m_vecAcceleration * p_deltaTime;
    m_vecVelocity = m_vecVelocity.limit( m_flMaxSpeed );
    m_vecPosition += m_vecVelocity * p_deltaTime;

    if( m_vecPosition.x < 0 ) m_vecPosition.x = 640;
    else if ( m_vecPosition.x > 640 ) m_vecPosition.x = 0;

    if( m_vecPosition.y < 0 ) m_vecPosition.y = 480;
    else if( m_vecPosition.y > 480 ) m_vecPosition.y = 0;
}

Vector CBoid::align( CBoid* p_flock, int p_flockSize )
{
    // get boids that we see (use squared distance)

    // steering force, will be added to
    Vector avgHeading;
    int flockmateCount = 0;
    for( int i = 0; i < p_flockSize; i++ )
    {
        // don't count us
        if( &p_flock[i] == this ) continue;

        // don't count far boids
        if( vecDistance2( m_vecPosition, p_flock[i].m_vecPosition ) > m_iPerception2 ) continue;
        
        // add their direction to the average
        avgHeading += p_flock[i].m_vecVelocity.normalize();

        // keeping track of local flock size
        flockmateCount++;
    }

    // avoid divisions by zero
    if( flockmateCount == 0 ) return g_vecZero;

    avgHeading /= flockmateCount;
    Vector steering = avgHeading.setMag( m_flMaxSpeed ) - m_vecVelocity;
    steering = steering.limit( m_flMaxForce );
    return steering;
}

Vector CBoid::cohese( CBoid* p_flock, int p_flockSize )
{
    // get boids that we see (use squared distance)

    // steering force, will be added to
    Vector avgPos;
    int flockmateCount = 0;
    for( int i = 0; i < p_flockSize; i++ )
    {
        // don't count us
        if( &p_flock[i] == this ) continue;

        // don't count far boids
        if( vecDistance2( m_vecPosition, p_flock[i].m_vecPosition ) > m_iPerception2 ) continue;
        
        // add their position to the average
        avgPos += p_flock[i].m_vecPosition;

        // keeping track of local flock size
        flockmateCount++;
    }

    // avoid divisions by zero
    if( flockmateCount == 0 ) return g_vecZero;

    avgPos /= flockmateCount;
    // normalization isn't required
    Vector desired = ( avgPos - m_vecPosition ).setMag( m_flMaxSpeed );
    Vector steering = desired - m_vecVelocity;
    steering = steering.limit( m_flMaxForce );
    return steering;
}

Vector CBoid::separate( CBoid* p_flock, int p_flockSize )
{
    // get boids that we see (use squared distance)

    // repulsion
    Vector repulsionForce;
    for( int i = 0; i < p_flockSize; i++ )
    {
        // don't count us
        if( &p_flock[i] == this ) continue;

        float dist = vecDistance2( m_vecPosition, p_flock[i].m_vecPosition );

        // don't count far boids
        if( dist > m_iPerception2 ) continue;

        // get our inverted difference and divide it by our distance to it squared (inverse square law)
        Vector diff = m_vecPosition - p_flock[i].m_vecPosition;     // inverted difference
        diff /= dist;
        repulsionForce += diff;
    }

    Vector steering = repulsionForce.setMag( m_flMaxSpeed ) - m_vecVelocity;
    steering = steering.limit( m_flMaxForce );
    return steering;
}

Vector CBoid::getPosition() const
{
    return m_vecPosition;
}