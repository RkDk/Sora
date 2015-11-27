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
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/foreach.hpp>

#define TEXTURE_RENDER_WIDTH 85
#define TEXTURE_RENDER_HEIGHT 85

class CLevelTile {
  
public:
    
    int texID;
    float x, y;
    float w, h;
    float s, t, n, m;
    
};

class CTextureInfo {
    
public:
    
    int textureListIndex, tileFlags;
    Vector2< int > worldPos;
    
    CTextureInfo() { }
    
    CTextureInfo( int id, int x, int y ) : textureListIndex( id ), worldPos( x, y ) {
        
    }
    
};

class CLevel {
    
private:
    
    CTextureSheet m_LevelTextureSheet;
    std::vector< CTextureInfo > m_textureInfoList;
    boost::ptr_vector< CLevelTile > m_vTiles;
    
    std::unordered_map< int, std::string > m_textureList;
    std::unordered_map< int, CTextureImage * > m_textureData;
    std::unordered_map< int, Vector4< float > > m_textureCoord;
    
    std::string m_Path;
    
    int m_LastTextureKey;
    
    void CreateNewTile( int, int, int );
    
public:
    
    std::string GetPath() {
        return m_Path;
    }
    
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
