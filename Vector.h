#ifndef VECTOR_H_
#define VECTOR_H_

template< class T >
class Vector3
{

private:

	T x, y, z;

public:

    Vector3( T _x, T _y ) : x( _x ), y( _y ), z( ( T )0 )
    {

    }

    Vector3( T _x, T _y, T _z ) : x( _x ), y( _y ), z( _z )
    {

    }

    Vector3() : x( ( T )0 ), y( ( T )0 ), z( ( T )0 )
    {


    }

	void Set( T _x, T _y ) { x = _x; y = _y; }
	void Set( T _x, T _y, T _z ) { x = _x; y = _y; z = _z; }

	void SetX( T _x ) { x = _x; }
	void SetY( T _y ) { y = _y; }
	void SetZ( T _z ) { z = _z; }

	void Get( T * _x, T * _y ) { *_x = x; *_y = y; }
	void Get( T * _x, T * _y, T * _z ) { *_x = x; *_y = y; *_z = z; }

	T GetX() { return x; }
	T GetY() { return y; }
	T GetZ() { return z; }

};

#endif
