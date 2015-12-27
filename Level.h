#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <sstream>
#include <string>
#include <unordered_map>
#include "TextureSheet.h"
#include "Util.h"
#include "TextureImage.h"
#include "TextureSheet.h"
#include "TextureFactory.h"
#include "DrawContext.h"
#include "BaseSpatialTreeEntity.h"
#include "SpatialTree.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/foreach.hpp>

#define TEXTURE_RENDER_WIDTH 142
#define TEXTURE_RENDER_HEIGHT 142

#define TILE_FLAG_NONE 0
#define TILE_FLAG_WALL 0x01

class CLevelTile {
  
public:
    
    int texID, tileInfoIndex;
    float x, y;
    float w, h;
    float s, t, n, m;
    
};

class CTextureInfo {
    
public:
    
    int textureListIndex, tileFlags;
    Vector2< int > worldPos;
    
    CTextureInfo() : tileFlags( 0 ) { }
    
    CTextureInfo( int id, int x, int y ) : textureListIndex( id ), worldPos( x, y ), tileFlags( 0 ) {
        
    }
    
};

class CLevelEntityInfo {
    
public:
    
    float x, y;
    int entID, entValue1, entValue2, entValue3;
    
    CLevelEntityInfo( int id, float _x, float _y, int v1, int v2, int v3 ) : entID( id ), x( _x ), y( _y ), entValue1( v1 ), entValue2( v2 ), entValue3( v3 ) {
        
    }
    
    CLevelEntityInfo() : entID( -1 ), entValue1( 0 ), entValue2( 0 ), entValue3( 0 ), x( 0.0f ), y( 0.0f ) {
    }
    
};

class CLevelTileEntity : public CWorldEntity {
    
private:
 
public:
    
    CLevelTileEntity() : CWorldEntity() {
        m_ClassTypeID = WORLD_ENTITY_WALL_ID; //SPECIAL WALL TYPE ID
    }
  
    virtual ~CLevelTileEntity() { }
    
};

class CLevelEditorCallback {
    
public:
    
    virtual void HandleTileCreation( CTextureInfo & t ) {
        
    }
    
    virtual void HandleEntityCreation( CLevelEntityInfo & e ) {
        
    }
    
};


class CLevel {
    
private:
    
    CLevelEditorCallback * m_pEditorCallback;
    CTextureSheet m_LevelTextureSheet;
    std::vector< CTextureInfo > m_textureInfoList;
    std::vector< CLevelEntityInfo > m_entityInfoList;
    boost::ptr_vector< CLevelTileEntity > m_vSpatialTiles; //This entity list exists for the sake of the spatial tree
    boost::ptr_vector< CLevelTile > m_vTiles;
    
    std::unordered_map< int, std::string > m_textureList;
    std::unordered_map< int, CTextureImage * > m_textureData;
    std::unordered_map< int, Vector4< float > > m_textureCoord;
    
    std::string m_Path;
    
    int m_LastTextureKey;
    
    CLevelTileEntity * GetSpatialTile( float, float );
    
    void CreateNewTile( int, int, int, int );
    void CreateNewTile( int, int, int );
    
public:
    
    CLevel() : m_pEditorCallback( nullptr ) {
        
    }
    
    std::string GetPath() {
        return m_Path;
    }
    
    void SetEditorCallback( CLevelEditorCallback * p ) {
        m_pEditorCallback = p;
    }
    
    void CreateNewEntity( int, float, float, int, int, int );
    
    void UpdateSpatialTree( CSpatialQuadTree * );
    void UpdatePackedTextureCoords();
    void CreatePackedTexture();
    bool HasLevelTexture( std::string );
    void AddLevelTexture( std::string, CTextureImage * image );
    int GetLevelTextureCount( std::string );
    void RemoveLevelTexture( std::string );
    
    void SetTileAt( std::string, int, int );
    void RemoveTileAt( int, int );
    
    void Save( std::string );
    void Load( std::string, CTextureFactory * );
    void Draw( CDrawContext * );
    
    CTextureSheet & GetPackedTextureSheet() {
        
        return m_LevelTextureSheet;
        
    }
    
};

#endif
