#ifndef VECTOR_H_
#define VECTOR_H_

template< class T >
class Vector2
{

protected:

	T x, y;

public:

    Vector2( T _x, T _y ) : x( _x ), y( _y )
    {

    }

    Vector2() : x( ( T )0 ), y( ( T )0 )
    {


    }

	void Set( T _x, T _y ) { x = _x; y = _y; }

	void SetX( T _x ) { x = _x; }
	void SetY( T _y ) { y = _y; }

	void Get( T * _x, T * _y ) const { *_x = x; *_y = y; }

	T GetX() { return x; }
	T GetY() { return y; }


};

template< class T >
class Vector3 : public Vector2< T >
{

private:

	T z;

public:

    Vector3( T _x, T _y ) : Vector2( _x, _y ), z( ( T )0 )
    {

    }

    Vector3( T _x, T _y, T _z ) : Vector2( _x, _y ), z( _z )
    {

    }

    Vector3() : Vector2(), z( ( T )0 )
    {


    }

	void Set( T _x, T _y, T _z ) { x = _x; y = _y; z = _z; }
	void SetZ( T _z ) { z = _z; }
	void Get( T * _x, T * _y, T * _z ) const { *_x = x; *_y = y; *_z = z; }
	T GetZ() { return z; }

};

template< class T >
class Vector4 : public Vector3< T >
{

private:

	T w;

public:

    Vector4( T _x, T _y ) : Vector3( _x, _y , ( T )0 ), w( ( T )0 )
    {

    }

    Vector4( T _x, T _y, T _z ) : Vector3( _x, _y, _z ), w( ( T )0 )
    {

    }


    Vector4( T _x, T _y, T _z, T _w ) : Vector3( _x, _y, _z ), w( ( T )_w )
    {

    }


    Vector4() : Vector3(), w( ( T )0 )
    {


    }

	void Set( T _x, T _y, T _z, T _w ) { x = _x; y = _y; z = _z; w = _w; }
	void SetW( T _w ) { w = _w; }
	void Get( T * _x, T * _y, T * _z, T * _w ) const { *_x = x; *_y = y; *_z = z; *_w = w; }
	T GetW() { return w; }

};



#endif
