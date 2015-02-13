#ifndef FONTMATERIAL_H_
#define FONTMATERIAL_H_

#include "ft2build.h"
#include FT_FREETYPE_H

#include "SDL_includes.h"

#include <GL/glew.h>

#include <string>
#include "Util.h"
#include "Vector.h"
#include "Logging.h"
#include "TextureSheet.h"
#include "DrawContext.h"

#define FONT_ALLOC 256

class CFontCharacter
{
    
public:
    
    Vector2< float > m_Size;
    Vector2< float > m_UpperLeftST, m_LowerRightST;
    long int m_Trans;
    long int m_Down, m_Left;
    int m_Offset;
    
    CFontCharacter() : m_Trans( 0 ), m_Down( 0 ), m_Left( 0 ), m_Offset( 0 ) {
    }
    
};


class CFontMaterial {
    
private:

    CFontCharacter m_Characters[FONT_ALLOC];
    CTextureSheet m_FontSheet;
    
    int m_FontSize;
  
public:
    
    int GetStringWidth( std::string );
    
    void DrawString( CDrawContext *, std::string, float, float, float, float, float, float );
    
    CTextureSheet & GetFontSheet() {
     
        return m_FontSheet;
        
    }
    
    void Load( std::string, FT_Library &, int );
    
};

#endif
