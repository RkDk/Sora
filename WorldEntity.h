#ifndef WORLDENTITY_H_
#define WORLDENTITY_H_

#include "Vector.h"
#include "Entity.h"
#include "Sprite.h"
#include "TextureImage.h"
#include "Matrix.h"
#include "CollisionBody.h"
#include <Box2D/Box2D.h>

class CBaseQuadTreeEntity {
    
protected:
    
    
    Vector2< float > m_Pos, m_Size;
    int m_EntityID;
    bool m_bShouldKill;
    bool m_bShouldUpdate;
    
    
public:
    
    CBaseQuadTreeEntity() : m_EntityID( -1 ), m_bShouldKill( false ), m_bShouldUpdate( false ) {
        
    }
    
    void SetEntityID( int id ) {
        
        m_EntityID = id;
        
    }
    
    int GetEntityID() {
        
        return m_EntityID;
        
    }
    
    void SetPos( float x, float y ) {
        
        m_Pos.Set( x, y );
        
    }
    
    void SetSize( float x, float y ) {
        
        m_Size.Set( x, y );
        
    }
    
    void GetPos( float * x, float * y ) {
        
        *x = m_Pos.GetX();
        *y = m_Pos.GetY();
        
    }
    
    void GetSize( float * x, float * y ) {
        
        *x = m_Size.GetX();
        *y = m_Size.GetY();
        
    }
    
    void SetShouldKill( bool b ) {
    
        m_bShouldKill = b;
        
    }
    
    bool GetShouldKill() {
     
        return m_bShouldKill;
        
    }
    
    void SetShouldUpdate( bool b ) {
     
        m_bShouldUpdate = b;
        
    }
    
    bool GetShouldUpdate() {
     
        return m_bShouldUpdate;
        
    }
    
};

/*


//10 meter in Box2d = 5 pixels
//Maybe make configurable per game project?
#define BOX2D_METER2PIXEL .5f
#define BOX2D_PIXEL2METER 2.0f

class CPhysBody
{

private:

    Vector3< float > m_Size;

    b2World * m_pRefWorld;
    b2Body * m_pBoxBody;
    b2Fixture * m_pBoxFixture;

public:

    bool Initialize();

    CPhysBody() : m_pRefWorld( NULL ), m_pBoxBody( NULL ), m_pBoxFixture( NULL )
    {

    }
    

    void SetReferenceWorld( b2World * w )
    {

        m_pRefWorld = w;

    }

    void SetGravity( int g )
    {

        m_pBoxBody->SetGravityScale( 0 );

    }
    
    const Vector3< float > & GetSize() const {
        
        return m_Size;
        
    }

    void SetSize( Vector3< float > v )
    {

        m_Size = v;

    }
    

    void SetPos( float x, float y )
    {

		m_pBoxBody->SetTransform( b2Vec2( x, y ), m_pBoxBody->GetAngle() );

    }

    void SetPos2( float x, float y, float w, float h )
    {

		x = ( x + w * .5f ) * BOX2D_PIXEL2METER;
		y = ( y + h * .5f ) * BOX2D_PIXEL2METER;

		SetPos( x, y );

    }

    b2Vec2 GetPos()
    {

        return m_pBoxBody->GetPosition();

    }

    void SetBodyData( void * data )
    {

        m_pBoxBody->SetUserData( data );

    }

    ~CPhysBody();

};
 
 */

class CWorldEntity : public CEntity
{

protected:

    CSprite m_Sprite;

    bool m_bMoved;
    
    Vector3< float > m_Position;
    //bool m_bPhysicsBodyInit, m_bExplicitPhysicsBodyPosSet, m_bFollowPhysics;
    //CPhysBody m_PhysicsBody;
    CCollisionBody * m_pCollisionBody;
    CBaseQuadTreeEntity * m_pQuadTreeEntity;

public:
    
    void FitIn( float x1, float y1, float x2, float y2 ) {
     
        float curx = m_Position.GetX(), cury = m_Position.GetY();
        
        if( curx < x1 )
            curx = x1;
        else if( curx > x2 )
            curx = x2;
        
        if( cury < y1 )
            cury = y1;
        else if( cury > y2 )
            cury = y2;
        
        m_Position.Set( curx, cury );
        
    }
    
    void SetCollisionBody( CCollisionBody * pCollisionBody ) {
     
        m_pCollisionBody = pCollisionBody;
        
    }
    
    CSprite & GetSprite() {
     
        return m_Sprite;
        
    }
    
    CCollisionBody * GetCollisionBody() {
     
        return m_pCollisionBody;
        
    }
    
    /*
    
    void AddSize( float x, float y ) {
        
    
        Vector3< float > s = m_PhysicsBody.GetSize();
        float newx = x * BOX2D_PIXEL2METER + s.GetX();
        float newy = y * BOX2D_PIXEL2METER + s.GetY();
     
        m_PhysicsBody.SetSize( Vector3< float >( newx, newy ) );
      
     
     
    }*/

    void Displace2( float x, float y )
    {
        x *= m_pContext->GetFrameDelta();
        y *= m_pContext->GetFrameDelta();

        Displace( x, y );

    }

    void Displace( float x, float y )
    {

        m_Position.Set( m_Position.GetX() + x, m_Position.GetY() + y );
 //     m_bExplicitPhysicsBodyPosSet = true;

        m_bMoved = true;
        
    }
    
    /*

    void EnablePhysicsMovement()
    {

        m_bFollowPhysics = true;

    }

    void DisablePhysicsMovement()
    {

        m_bFollowPhysics = false;

    }

    void SetGravity( int g )
    {

        m_PhysicsBody.SetGravity( 0 );

    }
*/
    float GetX() const
    {

        return m_Position.GetX();

    }

    float GetY() const
    {

        return m_Position.GetY();

    }

    float GetRightX() const {
     
        return m_Position.GetX() + ( float )m_Sprite.GetSize().GetX();
        
    }

    float GetBottomY() const {
        
        return m_Position.GetY() + ( float )m_Sprite.GetSize().GetY();
        
    }
    
    float GetCenterX() const
    {
        
        return m_Position.GetX() + ( float )m_Sprite.GetSize().GetX() * .5f;
        
    }
    
    float GetCenterY() const
    {
        
        return m_Position.GetY() + ( float )m_Sprite.GetSize().GetY() * .5f;

    }

    
    const Vector3< float > & GetPos() const
    {

        return m_Position;

    }
    
    const Vector2< int > & GetSize() const
    {
        
        return m_Sprite.GetSize();
        
    }

    void SetPos( Vector3< float > & v )
    {

        m_Position = v;
        //m_bExplicitPhysicsBodyPosSet = true;
        
        m_bMoved = true;

    }

    void SetPos( float x, float y )
    {

        m_Position.Set( x, y );
        //m_bExplicitPhysicsBodyPosSet = true;
        
        m_bMoved = true;


    }

    void SetPos( float x, float y, float z )
    {

        m_Position.Set( x, y, z );
        //m_bExplicitPhysicsBodyPosSet = true;
        
        m_bMoved = true;


    }
    
    void SetPos( Vector2< float > & v ) {
     
        m_Position.Set( v.GetX(), v.GetY() );
        //m_bExplicitPhysicsBodyPosSet = true;
        
        m_bMoved = true;
        
    }

    void SetColor( float r, float g, float b, float a ) {
        
        
        m_Sprite.SetColor( r, g, b, a );
        
    }
    
    void SetScale( float x, float y ) {
     
        m_Sprite.SetScale( x, y );
        
    }
    
    void SetMaterial( CTextureImage * pTexImage )
    {

        m_Sprite.SetTexture( pTexImage );

    }

	void SetSize( int x, int y )
	{

		m_Sprite.SetSize( x, y );

	}

    //void CreatePhysicsBody( b2World *, float, float );

    void UpdateSprite();
    void DrawSprite();

    void BaseUpdate();
    void BaseDraw( CMatrix< float > *, bool );
    void BaseDraw( CMatrix< float > * );

    void BaseDraw();

    virtual void Update()
    {

        BaseUpdate();

    }

    virtual void Draw()
    {

        BaseDraw();

    }

    virtual bool IsDrawable()
    {

        return true;

    }
    
    void UpdateQuadTreeEntityPos() {
     
        Vector3< float > origin;
        
        if( m_pCollisionBody )
            origin = m_pCollisionBody->GetOrigin();
        
        m_pQuadTreeEntity->SetPos( m_Position.GetX() + origin.GetX(), m_Position.GetY() + origin.GetY() ) ;
        
    }

    void UpdateQuadTreeEntitySize() {
        
        Vector3< float > size;
        
        if( m_pCollisionBody )
            size = m_pCollisionBody->GetSize();
        
        m_pQuadTreeEntity->SetSize( size.GetX(), size.GetY() ) ;
        
    }
    
    
    void SetQuadTreeEntity( CBaseQuadTreeEntity * pQuadTreeEntity ) {
        
        m_pQuadTreeEntity = pQuadTreeEntity;
        m_pQuadTreeEntity->SetEntityID( GetGlobalCount() );
        
    }

    CWorldEntity() : CEntity(), m_pQuadTreeEntity( NULL ), m_bMoved( false ), m_pCollisionBody( NULL )
    {


    }

    virtual ~CWorldEntity() {
    
        if( m_pQuadTreeEntity )
            m_pQuadTreeEntity->SetShouldKill( true );
        
        if( m_pCollisionBody )
            delete m_pCollisionBody;
    
    }

};

#endif
