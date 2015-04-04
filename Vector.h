 #ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>

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

    const Vector2< T > & operator+( Vector2< T > & v ) {
        
        return Vector2< T >( this->GetX() + v.x, this->GetY() + v.y );
        
    }
    

    const Vector2< T > operator*( Vector2< T > & v ) {
        
        return Vector2< T >( this->GetX() * v.x, this->GetY() * v.y );
        
    }
    
    Vector2< T > operator*( float v ) {
        
        return Vector2< T >( this->GetX() * v, this->GetY() * v );
        
    }
    
    virtual T GetDotProduct( Vector2< T > & v ) {
     
        float x2 = v.GetX();
        float y2 = v.GetY();
        
        return ( x * x2 + y * y2 );
        
    }
    
    virtual T GetMagnitude() {
     
        return sqrt( x * x + y * y );
        
    }
    
    virtual void GetNormal( Vector2< T > * n ) {
     
        float m = GetMagnitude();
        float tx = x / m;
        float ty = y / m;
        
        n->Set( tx, ty );
        
    }
    
    void Normalize() {
     
        GetNormal( this );
        
    }

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
    
    
    Vector3< T > operator+( Vector3< T > & v ) const {
        
        return Vector3< T >( this->GetX() + v.x, this->GetY() + v.y, this->GetZ() + v.z );
        
    }
    
    Vector3< T > operator*( Vector3< T > & v ) {
        
        return Vector3< T >( this->GetX() * v.x, this->GetY() * v.y , this->GetZ() * v.z );
        
    }

    Vector3< T > operator*( float v ) {
        
        return Vector3< T >( this->GetX() * v, this->GetY() * v, z * v );
        
    }

    
    
    virtual T GetDotProduct( Vector3< T > & v ) {
        
        float x = this->x;
        float y = this->y;
        
        float x2 = v.GetX();
        float y2 = v.GetY();
        float z2 = v.GetZ();
        
        return ( x * x2 + y * y2 + z * z2 );
        
    }
    
    virtual T GetMagnitude() {
        
        float x = this->x;
        float y = this->y;
        
        return sqrt( x * x + y * y + z * z );
        
    }
    
    virtual void GetNormal( Vector3< T > * n ) {
        
        float x = this->x;
        float y = this->y;
        
        float m = GetMagnitude();
        float tx = x / m;
        float ty = y / m;
        float tz = z / m;
        
        n->Set( tx, ty, tz );
        
    }


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

    virtual T GetDotProduct( Vector4< T > & v ) {
        
        float x = this->x;
        float y = this->y;
        float z = this->z;
        
        float x2 = v.GetX();
        float y2 = v.GetY();
        float z2 = v.GetZ();
        float w2 = v.GetW();
        
        return ( x * x2 + y * y2 + z * z2 + w * w2 );
        
    }
    
    virtual T GetMagnitude() {
        
        float x = this->x;
        float y = this->y;
        float z = this->z;
        
        return sqrt( x * x + y * y + z * z + w * w );
        
    }
    
    virtual void GetNormal( Vector4< T > * n ) {
        
        float x = this->x;
        float y = this->y;
        float z = this->z;
        
        float m = GetMagnitude();
        float tx = x / m;
        float ty = y / m;
        float tz = z / m;
        float tw = w / m;
        
        n->Set( tx, ty, tz, tw );
        
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
