#include "FontMaterial.h"

void CFontMaterial::Load( std::string dir, FT_Library & ftLib ) {
    
    if( !Util::DoesFileExist( dir ) ) {
     
        Log::Error( "Attempted to load non-existant font " + dir );
        return;
        
    }
    
    FT_Face face;
    FT_New_Face( ftLib, dir.c_str(), 0, &face );
    FT_Set_Pixel_Sizes( face, 0, DEFAULT_FONT_HEIGHT );

    int sheetwidth = 0, sheetheight = 0;
    int offsetx = 0;
    
    for( int j = 0; j < FONT_ALLOC; j++ ) {
     
        FT_UInt glyphindex = FT_Get_Char_Index( face, j );
        FT_Load_Glyph( face, glyphindex, FT_LOAD_RENDER );
        FT_GlyphSlot slot = face->glyph;
        FT_Bitmap bitmap = slot->bitmap;
        
        sheetwidth += bitmap.width;
        sheetheight = ( bitmap.rows > sheetheight )? bitmap.rows : sheetheight;
        
    }
    
    m_FontSheet.InitPixels( sheetwidth, sheetheight );

    for( int j = 0; j < FONT_ALLOC; j++ )
    {
        
        FT_UInt glyphindex = FT_Get_Char_Index( face, j );
        FT_Load_Glyph( face, glyphindex, FT_LOAD_RENDER );
        FT_GlyphSlot slot = face->glyph;
        FT_Bitmap bitmap = slot->bitmap;
        
        long int down = ( slot->metrics.height - slot->metrics.horiBearingY ) >> 6;
        
        int w = bitmap.width;
        int h = bitmap.rows;
        
        GLubyte * data = new GLubyte[2 * w * h];
        
        for( int y = 0; y < bitmap.rows; y++ )
        {
            
            for( int x = 0; x < bitmap.width; x++ )
            {
                
                data[2 * ( x + y * w )] = bitmap.buffer[x + bitmap.width * y] > 0? 255 : 0;
                data[2 * ( x + y * w ) + 1] = bitmap.buffer[x + bitmap.width * y];
                
            }
            
        }

        m_Characters[j].m_CoordMul.Set( ( float )bitmap.width / ( float )w, ( float )bitmap.rows / ( float )h );
        m_Characters[j].m_Trans = face->glyph->advance.x >> 6;
        m_Characters[j].m_Left = face->glyph->bitmap_left;
        m_Characters[j].m_Size.Set( bitmap.width, bitmap.rows );
        m_Characters[j].m_Down = down;
        
        m_FontSheet.AddPixelDataLuminance( data, offsetx, 0, w, h );
        
        m_Characters[j].m_Offset = offsetx;
        offsetx += w;
        
        delete [] data;
   
        
    }
    
    FT_Done_Face( face );
    
    m_FontSheet.CreateGLTexture();
    
    Log::Debug( "Successfully loaded font " + dir );
    
}