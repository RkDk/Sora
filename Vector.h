#ifndef VECTOR_H_
#define VECTOR_H_

template< class T >
class Vector2
{

protected:

	T x, y;

public:

    Vector2<T>( T _x, T _y ) : x( _x ), y( _y )
    {

    }

    Vector2<T>() : x( ( T )0 ), y( ( T )0 )
    {


    }

	void Set( T _x, T _y ) { x = _x; y = _y; }

	void SetX( T _x ) { x = _x; }
	virtual void SetY( T _y ) { y = _y; }

	void Get( T * _x, T * _y ) const { *_x = x; *_y = y; }

	T GetX() const { return x; }
	T GetY() const { return y; }


};

template< class T >
class Vector3 : public Vector2< T >
{

protected:

	T z;

public:


    Vector3<T>( T _x, T _y ) : Vector2<T>( _x, _y ), z( ( T )0 )
    {

    }

    Vector3<T>( T _x, T _y, T _z ) : Vector2<T>( _x, _y ), z( _z )
    {

    }

    Vector3<T>() : Vector2<T>(), z( ( T )0 )
    {


    }

	using Vector2<T>::Set;
	using Vector2<T>::Get;

	void Set( T _x, T _y, T _z ) { this->x = _x; this->y = _y; this->z = _z; }
	void SetZ( T _z ) { z = _z; }
	void Get( T * _x, T * _y, T * _z ) const { *_x = this->x; *_y = this->y; *_z = this->z; }
	T GetZ() const { return z; }

};

template< class T >
class Vector4 : public Vector3< T >
{

private:

	T w;

public:

    Vector4( T _x, T _y ) : Vector3<T>( _x, _y , ( T )0 ), w( ( T )0 )
    {

    }

    Vector4( T _x, T _y, T _z ) : Vector3<T>( _x, _y, _z ), w( ( T )0 )
    {

    }


    Vector4( T _x, T _y, T _z, T _w ) : Vector3<T>( _x, _y, _z ), w( ( T )_w )
    {

    }


    Vector4() : Vector3<T>(), w( ( T )0 )
    {


    }


	using Vector2<T>::Set;
	using Vector2<T>::Get;

	using Vector3<T>::Set;
	using Vector3<T>::Get;

	void Set( T _x, T _y, T _z, T _w ) { this->x = _x; this->y = _y; this->z = _z; w = _w; }
	void SetW( T _w ) { w = _w; }
	void Get( T * _x, T * _y, T * _z, T * _w ) const { *_x = this->x; *_y = this->y; *_z = this->z; *_w = w; }
	T GetW() const { return w; }

};



#endif
