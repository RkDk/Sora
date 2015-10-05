#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <string>
#include "TextureSheet.h"
#include "TextureImage.h"
#include "DrawContext.h"

class CLevelTile {
  
public:
    
    float x, y;
    float s, t;
    
};

class CLevel {
    
private:
    
    CTextureSheet m_LevelTextureSheet;
    std::vector< CLevelTile * > m_vTiles;
    
public:
    
    void Load( std::string );
    void Draw( CDrawContext * );
    
};

#endif
