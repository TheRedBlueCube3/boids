#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
    Vector();
    Vector( float p_x, float p_y );

    float   x;
    float   y;

    void    operator =  ( const float value )           ;
    bool    operator == ( const Vector& other )    const;
    bool    operator == ( const float value )      const;
    bool    operator != ( const Vector& other )    const;
    bool    operator != ( const float value )      const;

    Vector& operator += ( const Vector& other )         ;
    Vector& operator += ( const float component )       ;
    Vector& operator -= ( const Vector& other )         ;
    Vector& operator -= ( const float component )       ;
    Vector& operator *= ( const float scalar )          ;
    Vector& operator /= ( const float scalar )          ;

    Vector  operator +  ( const Vector& other )    const;
    Vector  operator +  ( const float component )  const;
    Vector  operator -  ( const Vector& other )    const;
    Vector  operator -  ( const float component )  const;
    Vector  operator *  ( const float scalar )     const;
    float   operator *  ( const Vector& other )    const;
    Vector  operator /  ( const float scalar )     const;

    float   mag()                                  const;
    Vector  setMag( const float magnitude )        const;
    Vector  limit( const float magnitude )         const;
    Vector  normalize() const;
};

extern Vector g_vecZero;
extern Vector g_vecUp;
extern Vector g_vecDown;
extern Vector g_vecLeft;
extern Vector g_vecRight;


#endif
