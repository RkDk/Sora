#include "FontMaterial.h"

void CFontMaterial::DrawString( CDrawContext * pDrawContext, std::string text, float x, float y, float r, float g, float b, float a ) {
 
    float xtrans = 0.0f, ytrans = 0.0f;
    
    pDrawContext->SetTexture( m_FontSheet.GetTexture() );
    pDrawContext->SetDrawColor( r, g, b, a );
    
    for( int i = 0; i < text.length(); i++ ) {
        
        bool newline = false;
        
        if( text[i] == '\n' )
            newline = true;

        if( !newline ) {
        
            int c = text[i];
            CFontCharacter fchar = m_Characters[c];
            Vector2< float > size = fchar.m_Size;
            Vector2< float > v1 = fchar.m_UpperLeftST;
            Vector2< float > v2 = fchar.m_LowerRightST;
            
            pDrawContext->StartDraw();
                pDrawContext->SetPos( x + xtrans + fchar.m_Left, y + ytrans + m_FontSize + fchar.m_Down - size.GetY() );
                pDrawContext->SetScale( size.GetX() , size.GetY() );
                pDrawContext->SetTexCoord( v1.GetX(), v1.GetY(), v2.GetX(), v1.GetY(), v2.GetX(), v2.GetY(), v1.GetX(), v2.GetY() );
            pDrawContext->EndDraw();
            
            xtrans += fchar.m_Trans;
            
        } else {
         
            xtrans = 0;
            ytrans += m_FontSize;
            
        }
        
    }
    
}

void CFontMaterial::Load( std::string dir, FT_Library & ftLib, int fontsize ) {
    
    if( !Util::DoesFileExist( dir ) ) {
     
        Log::Error( "Attempted to load non-existant font " + dir );
        return;
        
    }
    
    m_FontSize = fontsize;
    
    FT_Face face;
    FT_New_Face( ftLib, dir.c_str(), 0, &face );
    FT_Set_Pixel_Sizes( face, 0, fontsize );

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
       
        m_Characters[j].m_Trans = face->glyph->advance.x >> 6;
        m_Characters[j].m_Left = face->glyph->bitmap_left;
        m_Characters[j].m_Size.Set( bitmap.width, bitmap.rows );
        m_Characters[j].m_Down = down;
        
        m_Characters[j].m_UpperLeftST.Set( ( float )offsetx / ( float )sheetwidth, 0.0f );
        m_Characters[j].m_LowerRightST.Set( ( ( float )offsetx + ( float )w ) / ( float )sheetwidth, ( ( float )down + ( float )h ) / ( float )sheetheight );
        
        m_FontSheet.AddPixelDataLuminance( data, offsetx, 0, w, h );
        
        m_Characters[j].m_Offset = offsetx;
        offsetx += w;
        
        delete [] data;
   
        
    }
    
    FT_Done_Face( face );
    
    m_FontSheet.CreateGLTexture();
    
    Log::Debug( "Successfully loaded font " + dir );
    
}