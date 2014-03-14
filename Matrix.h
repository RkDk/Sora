#ifndef MATRIX_H_
#define MATRIX_H_

#define RAD_CONSTANT 0.017453f

template< typename T >
class CMatrix
{

private:

	T m_RawMatrix[16];

public:

	void Identity()
	{

		T o = ( T )1;
		T z = ( T )0;

		T newMat[] =
		{

			o, z, z, z,
			z, -o, z, z,
			z, z, o, z,
			z, z, z, o

		};

		memcpy( m_RawMatrix, newMat, sizeof( T ) * 16 );

	}

	void Translate( T x, T y, T z )
	{

		m_RawMatrix[12] += x * m_RawMatrix[0];
		m_RawMatrix[13] += y * m_RawMatrix[5] * -1.0f;
		m_RawMatrix[14] += z * m_RawMatrix[10];

	}

	void Scale( T x, T y, T z )
	{

		m_RawMatrix[0] *= x;
		m_RawMatrix[5] *= y;
		m_RawMatrix[10] *= z;

		m_RawMatrix[12] *= x;
		m_RawMatrix[13] *= y;
		m_RawMatrix[14] *= z;

	}

	void Rotate( float theta, float x, float y, float z )
	{

		float s = sin( theta * RAD_CONSTANT );
		float c = cos( theta * RAD_CONSTANT );
		float oc = ( 1 - c );
		float oczx = oc * ( z * x );
		float ocxy = oc * ( x * y );
		float oczy = oc * ( y * z );
		float zs = z * s;
		float ys = y * s;
		float xs = x * s;

		T rotMat[] = 
		{

			oc * ( x * x ) + c, ocxy + zs, oczx - ys, 0,
			ocxy - zs, oc * ( y * y ) + c, oczy + xs, 0,
			oczx + ys, oczy - xs, oc * ( z * z ) + c, 0,
			0, 0, 0, 1

		};

		Mat4v4Multiply( rotMat );

	}

	void Mat4v4Multiply( T * mat )
	{

		T origMat[16];

		memcpy( origMat, m_RawMatrix, sizeof( T ) * 16 );

		for( int j = 0; j < 4; j++ )
		{
			
			for( int i = 0; i < 4; i++ )
			{

				m_RawMatrix[i + j * 4] = ( T )0;

				for( int n = 0; n < 4; n++ )
				{
					m_RawMatrix[i + j * 4] += origMat[n + j * 4] * mat[i + n * 4];
				}

			}

		}

	}

};

#endif