#include "Vector.h"
#include <cmath>

Vector g_vecZero( 0, 0 );
Vector g_vecUp( 0, 1 );
Vector g_vecDown( 0, -1 );
Vector g_vecLeft( -1, 0 );
Vector g_vecRight( 1, 0 );

Vector::Vector()
: x( 0 ), y( 0 )
{

}

Vector::Vector( float p_x, float p_y )
: x( p_x ), y( p_y )
{
    
}

void Vector::operator = ( const float value )
{
    x = value;
    y = value;
}

bool Vector::operator == ( const float value ) const
{
    return    x == value
           && y == value;
}
bool Vector::operator == ( const Vector& other ) const
{
    return    x == other.x
           && y == other.y;
}
bool Vector::operator != ( const float value ) const
{
    return    x != value
           && y != value;
}
bool Vector::operator != ( const Vector& other ) const
{
    return    x != other.x
           && y != other.y;
}

Vector& Vector::operator += ( const Vector& other )
{
    x += other.x;
    y += other.y;
    return *this;
}
Vector& Vector::operator += ( const float component )
{
    x += component;
    y += component;
    return *this;
}

Vector& Vector::operator -= ( const Vector& other )
{
    x -= other.x;
    y -= other.y;
    return *this;
}
Vector& Vector::operator -= ( const float component )
{
    x -= component;
    y -= component;
    return *this;
}

Vector& Vector::operator *= ( const float scalar )
{
    x *= scalar;
    y *= scalar;
    return *this;
}
Vector& Vector::operator /= ( const float scalar )
{
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector Vector::operator + ( const Vector& other ) const
{
    return Vector( x + other.x, y + other.y ); 
}

Vector Vector::operator + ( const float component ) const
{
    return Vector( x + component, y + component );
}

Vector Vector::operator - ( const Vector& other ) const
{
    return Vector( x - other.x, y - other.y ); 
}
Vector Vector::operator - ( const float component ) const
{
    return Vector( x - component, y - component ); 
}

Vector Vector::operator * ( const float scalar ) const
{
    return Vector( x * scalar, y * scalar ); 
}
float Vector::operator * ( const Vector& other) const
{
    return x * other.x + y * other.y;
}

Vector Vector::operator / ( const float scalar ) const
{
    return Vector( x / scalar, y / scalar ); 
}

float Vector::mag() const
{
    return std::sqrt( x * x + y * y );
}

Vector Vector::setMag( const float magnitude ) const
{
    float currMag = mag();

    if ( currMag == 0 )
    {
        return Vector( 0,0 );
    }

    return ( *this ) * ( magnitude / currMag );
}

Vector Vector::limit( const float magnitude ) const
{
    float currMag = mag();
    if ( currMag < magnitude )
    {
        return *this;
    }
    return setMag(magnitude);
}

Vector Vector::normalize() const
{
    return setMag(1);
}