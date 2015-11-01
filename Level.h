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
    
    float x, y;
    float w, h;
    float s, t, n, m;
    
};

class CLevel {
    
private:
    
    CTextureSheet m_LevelTextureSheet;
    boost::ptr_vector< CLevelTile > m_vTiles;
    
public:
    
    void Load( std::string, CTextureFactory * );
    void Draw( CDrawContext * );
    
    CTextureSheet & GetPackedTextureSheet() {
        
        return m_LevelTextureSheet;
        
    }
    
};

#endif
