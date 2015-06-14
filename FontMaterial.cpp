#include "FontMaterial.h"
#include <sstream>

void CFontMaterial::DrawString( CDrawContext * pDrawContext, std::string text, float x, float y, float r, float g, float b, float a, int type ) {
 
    float xtrans = 0.0f, ytrans = 0.0f;
    float xoffset = 0.0f, yoffset = 0.0f;
    
    x = ( int )x;
    y = ( int )y;
    
    pDrawContext->SetTexture( m_FontSheet.GetTexture() );
    pDrawContext->SetDrawColor( r, g, b, a );
    
    if( type & ( DRAW_TEXT_HORIZ_CENTER | DRAW_TEXT_VERT_CENTER ) ) {
     
        Vector2< int > size = GetStringSize( text );
        
        if( type & DRAW_TEXT_HORIZ_CENTER ) {
         
            xoffset = ( float )-size.GetX() * .5f;
            
        }

        if( type & DRAW_TEXT_VERT_CENTER ) {
            
            yoffset = ( float )-size.GetY() * .5f;
            
        }
        
    }
    
    xoffset = ( int )xoffset;
    yoffset = ( int )yoffset;
    
    
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
                pDrawContext->SetPos( x + xoffset + xtrans + fchar.m_Left, y + yoffset + ytrans - fchar.m_Down + m_LargestBearingY );
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


void CFontMaterial::DrawString( CDrawContext * pDrawContext, std::string text, float x, float y, float r, float g, float b, float a ) {
 
    DrawString( pDrawContext, text, x, y, r, g, b, a, DRAW_TEXT_LEFT );
    
}

std::string CFontMaterial::MakeFit( std::string text, int maxwidth ) {
 
    int width = 0;
    int lastspace = -1;
    int lastspacesize = 0;
    
    for( int i = 0; i < text.length(); i++ ) {
        
        bool newline = false;
        
        if( text[i] == '\n' )
            newline = true;
        
        if( text[i] == ' ' ) {
            
            lastspace = i;
            lastspacesize = width;
            
        }
        
        if( !newline ) {
            
            int c = text[i];
            CFontCharacter fchar = m_Characters[c];
            
            width += fchar.m_Trans;
    
            if( width >= maxwidth ) {
             
                if( lastspace > -1 ) {
                 
                    text[lastspace] = '\n';
                    width -= lastspacesize;
                    lastspace = -1;
                    
                }
                
            }
            
        } else {
            
            width = 0;
            lastspace = -1;
            
        }
        
    }
    
    return text;
    
}


Vector2< int > CFontMaterial::GetStringSize( std::string text ) {

    int width = 0, height = m_FontSize;
    int largestwidth = 0;
    
    for( int i = 0; i < text.length(); i++ ) {
        
        bool newline = false;
        
        if( text[i] == '\n' )
            newline = true;
        
        if( !newline ) {
            
            int c = text[i];
            CFontCharacter fchar = m_Characters[c];
            
            width += fchar.m_Trans;
            
        } else {
            
            width = 0;
            height += m_FontSize;
        
        }
        
        if( largestwidth < width )
            largestwidth = width;
        
        
    }
    
    return Vector2< int >( largestwidth, height );
    
}


int CFontMaterial::GetStringWidth( std::string text ) {
    
    Vector2< int > v = GetStringSize( text );
    
    return v.GetX();
    
}

int CFontMaterial::GetStringHeight( std::string text ) {
    
    Vector2< int > v = GetStringSize( text );
    
    return v.GetY();
    
}

void CFontMaterial::Load( std::string dir, FT_Library & ftLib, int fontsize ) {
    
    if( !Util::DoesFileExist( dir ) ) {
     
        Log::Error( "Attempted to load non-existant font " + dir );
        return;
        
    }
    
    m_FontSize = fontsize;
    m_LargestBearingY = 0;

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
        m_Characters[j].m_Down = slot->metrics.horiBearingY >> 6;
        m_Characters[j].m_Height = slot->metrics.height >> 6;
        
        if( m_LargestBearingY < m_Characters[j].m_Down )
            m_LargestBearingY = m_Characters[j].m_Down;
        
        m_Characters[j].m_UpperLeftST.Set( ( float )offsetx / ( float )sheetwidth, 0.0f );
        m_Characters[j].m_LowerRightST.Set( ( ( float )offsetx + ( float )w ) / ( float )sheetwidth, ( ( float )h ) / ( float )sheetheight );
        
        m_FontSheet.AddPixelDataLuminance( data, offsetx, 0, w, h );
        
        m_Characters[j].m_Offset = offsetx;
        offsetx += w;
        
        delete [] data;
   
        
    }
    
    FT_Done_Face( face );
    
    m_FontSheet.CreateGLTexture();
    
    std::stringstream log;
    log << "Successfully loaded font " << dir << " at size: " << fontsize;
    
    Log::Log( log.str() );
    
}